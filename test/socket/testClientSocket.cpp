#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

using namespace std;

int main(){
    // initialize socket client
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        cout << "socket error" << endl;
        return -1;
    }

    // connect to socket server
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = connect(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        cout << "connect error" << endl;
        return -1;
    }

    // write to socket server
    write(socketfd, "I'm alive", 25);

    // read from socket server
    char buf[1024];
    int n = read(socketfd, buf, sizeof(buf));
    cout << "read from socket server: " << buf << endl;

    // close socket client
    close(socketfd);

    return 0;
}