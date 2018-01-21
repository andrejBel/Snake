#include "Server.h"
#include <cstring>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include "packet.h"

Server::Server(const int portNumber, const unsigned char numberOfPlayers, bool& success) :
threadPool_(std::min((unsigned char) thread::hardware_concurrency(), numberOfPlayers)),
game_(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT, numberOfPlayers),
numberOfPlayers_(numberOfPlayers)
{

    initConnection(portNumber, success );

}

void 
Server::initConnection(const int portNumber, bool& success)
{
    int sockfd_, newsockfd_;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0)
    {
        std::cerr << "ERROR opening socket\n";
        success = false;
        return;
    }
    memset(&serv_addr, '\0', sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);
    if (bind(sockfd_, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
    {
        std::cerr << "ERROR on binding\n";
        success = false;
        return;
    }

    listen(sockfd_, CONSTANTS::MAX_NUM_OF_PLAYERS);
    int succesfullConnections = 0;
    while (succesfullConnections < numberOfPlayers_)
    {
        clilen = sizeof (cli_addr); // pozor zmena malo bzt ya listen
        newsockfd_ = accept(sockfd_, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd_ < 0)
        {
            std::cerr << "ERROR on accept\n";
            success = false;
            return;
        }
        else
        {
            clients_.push_back(new Client(newsockfd_, succesfullConnections));
            threadPool_.addTask([this, newsockfd_, succesfullConnections] ()
            {
                sendInitialInfo(newsockfd_, succesfullConnections);
            }

            );
            succesfullConnections++;
        }
    }
    threadPool_.finishAll();
    std::cout << "All clients connected\n";
    string buf = "start";
    for_each(clients_.begin(), clients_.end(), [&threadPool_ = threadPool_, &buf = buf] (Client * client){
        threadPool_.addTask(
        //std::bind(&Client::signalStart, std::ref(*client), buf)
        [client, &buf = buf] ()
        {
            client->send(buf);
        }
        );
    });
    threadPool_.finishAll();
    success = true;
}

Server::~Server()
{
    std::cout << "Server destruction\n";
    for (Client* client : clients_)
    {
        delete client;
    }
    close(sockfd_);
};

void
Server::sendInitialInfo(const int socketNumber, const int id)
{
    using namespace PACKETS;
    InitialPacket packet;

    game_.fillInitialPacket(packet, id);
    string buffer = packet.serialize();
    int n = write(socketNumber, buffer.c_str(), sizeof (InitialPacket));
    if (n < 0)
    {
        std::cout << "ERROR writing to socket\n";
        throw "ERROR writing to socket";
    }
}

void
Server::synchronizeWithClients()
{
    using namespace PACKETS;
    PlayerPacket packets[numberOfPlayers_];
    GamePacket gamePacket;
    for_each(clients_.begin(), clients_.end(), [&threadPool_ = threadPool_, &packets = packets] (Client * client){
        threadPool_.addTask(
        [client, &packets] ()
        {
            if (client->isListening())
            {
                client->getPlayerState(packets[client->getId()]);
            }
        }
        );
    });
    threadPool_.finishAll();
    for (int i = 0; i < numberOfPlayers_; i++)
    {
        cout << "smer x: " << +packets[i].actualDirection_.x << endl;
        cout << "smer y: " << +packets[i].actualDirection_.y << endl;
        cout << "stlacene tlacidlo: " << packets[i].touched_button_ << endl;
    }
    cout << "koniec\n";
    game_.tick(packets, gamePacket);
    

    
    
    game_.print();
    for_each(clients_.begin(), clients_.end(), [&threadPool_ = threadPool_, &gamePacket = gamePacket] (Client * client){
        threadPool_.addTask(
        [client, &gamePacket] ()
        {
            if (client->isListening())
            {
                client->sendGameState(gamePacket);
            }
        }
        );
    });
    threadPool_.finishAll();
    
}

void
Server::gameLoop()
{
    while (true)
    {
        this_thread::sleep_for(CONSTANTS::SYNCHRONIZE_TIME);
        synchronizeWithClients();
        int numberOfPlayersListening(0);
        for (int i = 0; i < numberOfPlayers_; i++)
        {
            if (clients_[i]->isListening())
            {
                numberOfPlayersListening++;
            }
        }
        if (numberOfPlayersListening <= 1) 
        {
            break;
        }
    }


}



