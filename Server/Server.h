
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <functional>

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Client.h"
#include "ThreadPool.h"
#include "Game.h"


using namespace std;
using namespace sf;

class Server {
    
public:
    Server(const int portNumber, const unsigned char numberOfPlayers, bool& success);
    ~Server();
    
    void gameLoop();
    

private:
    //atributes
    const unsigned char numberOfPlayers_;
    ThreadPool threadPool_;
    int sockfd_;
    vector<Client *> clients_;
    Game game_;
    
    
    //functions
    
    void initConnection(const int portNumber, bool& success);
    
    void sendInitialInfo(const int socketNumber, const int id);   
    
    void synchronizeWithClients();
    
};
