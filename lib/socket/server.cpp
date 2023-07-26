#include "server.h"

using namespace std;

Server::Server()
{
    // initialize socket server
    this->initServer();
    // bind socket server to port 8080
    this->bindServer();
    // listen to socket server
    this->listenClient();
    // accept connection from client
    this->acceptClient();
}

Server::~Server()
{
    // close socket server
    this->closeServer();
}

void Server::initServer()
{
    // initialize socket server
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

void Server::bindServer()
{
    // bind socket server to port 8080
    int ret = bind(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        cout << "bind error" << endl;
        exit(-1);
    }
}

void Server::listenClient()
{
    // listen to socket server
    int ret = listen(socketfd, 10);
    if (ret < 0)
    {
        cout << "listen error" << endl;
        exit(-1);
    }
}

void Server::acceptClient()
{
    // accept connection from client
    cout << "waiting for connection" << endl;
    socklen_t clientAddrLen = sizeof(clientAddr);
    this->clientfd = accept(socketfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientfd < 0)
    {
        cout << "accept error" << endl;
        exit(-1);
    }
}

void Server::startServer(){
    // initialize socket server
    this->initServer();
    // bind socket server to port 8080
    this->bindServer();
    // listen to socket server
    this->listenClient();
    // accept connection from client
    this->acceptClient();
}

string Server::readClient()
{
    // read from client
    char buf[1024];
    int n = read(clientfd, buf, sizeof(buf));
    return buf;
}

void Server::writeClient(string msg)
{
    // write to client
    write(clientfd, msg.c_str(), msg.length()+1);
}

void Server::closeServer()
{
    // close socket server
    close(socketfd);
}
