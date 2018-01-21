#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "packet.h"

using namespace std;
using namespace sf;

class Client 
{
public:
    Client(string hostname, int portNumber, string & message,bool& success);
    
    void getInitialGameInfo(PACKETS::InitialPacket& gameInfo);
    void getGameState(PACKETS::GamePacket& gamePacket);
    
    void sendMessage(const string& buffer);
    void recieveMessage(string& buffer, int size);
    void recieveSignal();
    
    ~Client();
    
private:
    int sockfd_;
    
    
};