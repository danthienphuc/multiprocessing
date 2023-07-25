#include "../lib/fileIO.h"

using namespace std;

int main(){
    FileIO fileIO;
    int i = 0;

    // write file
    // fileIO.write("emails/email_1.csv", "Sender 1,Receiver 1,Subject 1,This is the content of email 1.");
    // fileIO.write("emails/email_2.csv", "Sender 2,Receiver 2,Subject 2,This is the content of email 2.");

    // read file
    string email = fileIO.read("emails/email_1.csv");
    cout << email << endl;
    email = fileIO.read("emails/email_2.csv");
    cout << email << endl;

    // list files
    string *files = fileIO.listFiles("/data/emails", ".csv");
    while(files[i] != ""){
        cout << "file " << i << ": " << files[i] << endl;
        i++;
    }
    return 0;
}