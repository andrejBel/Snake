#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "client.h"
#include "Game.h"


using namespace std;
using namespace sf;


int main(int argc, char* argv[])
{
    if (argc != 3) 
    {
        std::cerr << "usage " << argv[0] << " server_name port_number\n";
        return 1;
    }
    string message;
    bool success = false;
    Client client(argv[1], stoi(argv[2]), message, success);
    cout << message << endl;


    if (success)
    {
        PACKETS::InitialPacket startInfo;
        client.getInitialGameInfo(startInfo);

        if (startInfo.id_ != startInfo.numberOfPlayers_ - 1) 
        {
            cout << "Waiting for other players to connect\n";
        }
        client.recieveSignal();
        Game(client, startInfo).run();
        cout << "Game finished\n";
    } else 
    {
        cout << "Game stopped\n";
    }
    
    return 0;
}
