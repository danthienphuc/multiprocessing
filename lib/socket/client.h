#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

using namespace std;

class Client
{
private:
    /* data */
    int socketfd;
    struct sockaddr_in serverAddr;
public:
    Client(/* args */);
    ~Client();

    void initClient();
    void connectServer();
    string readServer();
    void writeServer(string msg);
    void closeClient();
};

#endif // !CLIENT_H