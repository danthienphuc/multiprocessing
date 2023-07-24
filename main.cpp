#include <iostream>
#include <unistd.h>
#include "lib/fileIO.h"
#include "lib/sharedMemory.h"

using namespace std;

void parentProcess(SharedMemory shMem){
    printf("Parent process\n");
    FileIO fileIO;
    string email = fileIO.read("sender");
    shMem.write(email);
    printf("Parent process exit\n");
}

void childProcess(SharedMemory shMem){
    printf("Child process\n");
    int ppid = getppid();
    if(ppid==1){
        printf("%d Parent process of %d is dead\n", ppid, getpid());
    }
    else{
        printf("%d Parent process of %d is alive\n", ppid, getpid());
        string email;
        email = shMem.read();
        printf("Email from parent process:\n%s\n", email.c_str());
        FileIO fileIO;
        fileIO.write("receiver", email);
    }
    printf("Child process exit\n");
}

int main(){
    
    SharedMemory shMem;

    shMem.create(1024);

    int pid = fork();
    if(pid<0){
        printf("fork error\n");
        return -1;
    }
    else if(pid==0){
        childProcess(shMem);
        exit(0);
    }
    else{
        parentProcess(shMem);
    }


    return 0;
}