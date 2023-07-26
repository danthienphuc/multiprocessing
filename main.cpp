#include <iostream>
#include <unistd.h>
#include "lib/fileIO.h"
#include "lib/sharedMemory.h"
#include "lib/socket/server.h"
#include "lib/socket/client.h"

using namespace std;

bool compareStrings(string str1, string str2){
    for(int i=0;i<str2.length();i++){
        if(str1[i]!=str2[i]){
            return false;
        }
    }
    return true;
}

void sendEmail(Server server ,int i){
    string emailContent, clientMsg;
    server.writeClient("emailed\0");
    clientMsg = server.readClient();
    if(clientMsg=="done"){
        printf("Email %d sent\n",i);
    }
    else{
        printf("Email %d failed\n",i);
        sendEmail(server,i);
    }
}

void parentProcess(SharedMemory shMem){

    // init
    printf("Parent process\n");
    FileIO fileIO;
    string* emailList;
    emailList = fileIO.listFiles("/data/emails",".csv");
    // print email list    
    string emailContent;
    Server server;

    // check if child process is alive
    server.writeClient("is_alive");
    string clientMsg = server.readClient();
    cout << "Parent process: Client message: " << clientMsg << endl;

    // send emails
    if(compareStrings(clientMsg,"alive")){
        int i=0;
        while(emailList[i]!=""){
            // read an email
            // write it to shared memory
            // send a message to child process to read shared memory
            
            emailContent = fileIO.read("emails/" + emailList[i]);
            shMem.write(emailContent);
            cout << "Email " << i+1 << " is written to shared memory" << endl;
            sendEmail(server,i);
            i++;
        }
        server.writeClient("end");
    }
    // child process is not alive
    else{
        printf("Child process is not alive\n");
    }
    server.closeServer();
    printf("Parent process exit\n");
}

void childProcess(SharedMemory shMem){
    printf("Child process\n");
    sleep(1);
    Client client;
    string msg;

    while(true){
        msg = client.readServer();
        if(compareStrings(msg,"is_alive")){
            client.writeServer("alive");
        }
        else if(compareStrings(msg,"emailed")){
            string emailContent = shMem.read();
            FileIO fileIO;
            fileIO.write("email_archive.csv",emailContent);
            client.writeServer("done\0");
        }
        else if(compareStrings(msg,"end")){
            cout << "Child process: job finished" << endl;
            client.closeClient();
            break;
        }
        else
        {
            cout << "Child process: unknown message:" << msg << endl;
            client.writeServer("done\0");
        }
        
    }
    printf("Child process exit\n");
    exit(0);
}

void run(SharedMemory shMem){
    int pid = fork();
    if(pid<0){
        printf("fork error\n");
        run(shMem);
    }
    else if(pid==0){
        childProcess(shMem);
        exit(0);
    }
    else{
        parentProcess(shMem);
    }
}

int main(){
    
    SharedMemory shMem(1024);

    run(shMem);

    return 0;
}