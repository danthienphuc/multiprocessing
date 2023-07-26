// Socket server
// Host: Localhost
// Port: 8080
// Protocol: TCP
// Socket type: Stream socket
// Socket family: AF_INET
// Socket address:
//

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

using namespace std;

int main(){
    // initialize socket server
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        cout << "socket error" << endl;
        return -1;
    }

    // bind socket server to port 8080
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        cout << "bind error" << endl;
        return -1;
    }

    // listen to socket server
    ret = listen(socketfd, 10);
    if (ret < 0)
    {
        cout << "listen error" << endl;
        return -1;
    }

    // accept connection from client
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientfd = accept(socketfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientfd < 0)
    {
        cout << "accept error" << endl;
        return -1;
    }

    // read from client
    char buf[1024];
    int n = read(clientfd, buf, sizeof(buf));
    cout << "read from client: " << buf << endl;

    // write to client
    write(clientfd, "I'm alive", 25);

    // close socket server
    close(socketfd);

    return 0;
}
