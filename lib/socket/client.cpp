#include "client.h"

using namespace std;

Client::Client()
{
    // initialize socket client
    this->initClient();
    // connect to socket server
    this->connectServer();
}

Client::~Client()
{
    // close socket client
    this->closeClient();
}

void Client::initClient()
{
    // initialize socket client
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        cout << "socket error" << endl;
        exit(-1);
    }
}

void Client::connectServer()
{
    // connect to socket server
    cout << "Connecting to server..." << endl;
    int ret = connect(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        cout << "connect error" << endl;
        exit(-1);
    }
}

string Client::readServer()
{
    // read from socket server
    char buf[1024];
    int n = read(socketfd, buf, sizeof(buf));
    return buf;
}

void Client::writeServer(string msg)
{
    // write to socket server
    write(socketfd, msg.c_str(), msg.length());
}

void Client::closeClient()
{
    // close socket client
    close(socketfd);
}
