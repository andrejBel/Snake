#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

Client::Client(string hostname, int portNumber, string& message, bool& success)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0)
    {
        message = "Error connecting\n";
        success = false;
        return;
    }
    server = gethostbyname(hostname.c_str());
    if (server == NULL)
    {
        message = "ERROR, no such host\n";
        success = false;
        return;
    }
    memset(&serv_addr, '\0', sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portNumber);
    if (connect(sockfd_, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
    {
        message = "ERROR connecting to server\n";
        success = false;
        return;
    }
    message = "Connection to server successful\n";
    success = true;
}

void Client::sendMessage(const string& buffer)
    {

        int n = write(sockfd_, buffer.c_str(), buffer.size());
        if (n < 0)
        {
            cout << "ERROR writing to socket";
            throw "ERROR writing to socket";
        }
    }

 void Client::recieveMessage(string& buffer, int size)
    {
        buffer.resize(size);
        int n = read(sockfd_, (void *) buffer.c_str(), size);
        if (n < 0)
        {
            cout << "ERROR reading from socket";
            throw "ERROR reading from socket";
        }
    };
    
void Client::recieveSignal() 
{
    string buffer;
    buffer.resize(10);
    int n = read(sockfd_, (void *) buffer.c_str(), 10);
    if (n < 0)
    {
        cout << "ERROR reading from socket";
        throw "ERROR reading from socket";
    }
};    
 
void Client::getInitialGameInfo(PACKETS::InitialPacket& gameInfo)
{
    string infoFromServer;
    infoFromServer.resize(sizeof(PACKETS::InitialPacket));
    recieveMessage(infoFromServer, sizeof(PACKETS::InitialPacket));
    
    gameInfo.deserialize(infoFromServer);
}

void Client::getGameState(PACKETS::GamePacket& gamePacket) 
{
    string infoFromServer;
    infoFromServer.resize(sizeof(PACKETS::GamePacket));
    recieveMessage(infoFromServer, sizeof(PACKETS::GamePacket) );
    gamePacket.deserialize(infoFromServer);
}

    
Client::~Client() 
{
    close(sockfd_);
}

