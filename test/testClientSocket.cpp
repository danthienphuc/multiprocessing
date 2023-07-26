#include "../lib/socket/client.h"

using namespace std;

int main(){
    
    Client client;

    // write to socket server
    client.writeServer("I'm alive");

    // read from socket server
    string buf = client.readServer();
    cout << "read from socket server: " << buf << endl;

    return 0;
}