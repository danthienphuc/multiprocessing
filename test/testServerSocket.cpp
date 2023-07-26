#include "../lib/socket/server.h"

using namespace std;

int main(){
    Server server;

    // read from socket client
    string buf = server.readClient();
    cout << "read from socket client: " << buf << endl;

    // write to socket client
    server.writeClient("I'm alive");

    // close socket server
    server.closeServer();
    return 0;
}
