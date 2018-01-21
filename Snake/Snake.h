#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameArea.h"
#include <atomic>
#include "CONSTANTS.h"
#include <SFML/Graphics/Color.hpp>

#include "client.h"
#include "KeyboardInput.h"
#include <thread>

using namespace std;
using namespace sf;

class Snake
{
private:
        //attributes
    
	GameArea &area_;
        
	vector< vector< RectangleShape * > > bodies_;
        
        KeyboardInput keyboardInput_;
        
        const int id_;
        
        mutex mutex_;
        
        atomic<bool> ready_;
        
        atomic<bool> end_;
        
        const int numOfPlayers_;
        
        Client& client_;
        
        const int snakeWidth_;
        
        int score_;
        
        Font font_;
        Text textScore_;
        thread thread_;
        
        PACKETS::GamePacket gameState_;        
        
        bool windowTerminated_;
        
        //functions
        
        void communicateWithServer();
        
        
public:
	
	Snake(Vector2<unsigned char>* playerCoordinates,Vector2<char>* playerDirections ,const int width, const int id, const Keyboard::Key& leftKey, const Keyboard::Key& rightKey, GameArea& area, const int numOfPlayers, Client& client);

	void draw(RenderWindow &window);

	void update();
        
        void setWindowTerminated() 
        {
            windowTerminated_ = true;
        }
        
        bool isEnd() 
        {
            return end_;
        }

	~Snake();
};

