#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

using namespace std;

class Server
{
private:
    /* data */
    int socketfd;
    int clientfd;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

public:
    Server();
    ~Server();

    void initServer();
    void bindServer();
    void listenClient();
    void acceptClient();
    void startServer();
    string readClient();
    void writeClient(string msg);
    void closeServer();
};

#endif // !SERVER_H