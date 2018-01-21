/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: andrej
 *
 * Created on November 10, 2017, 6:51 PM
 */

#ifndef GAME_H
#define GAME_H
#include "client.h"
#include "GameArea.h"
#include "packet.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Snake.h"

using namespace std;
using namespace sf;

class Game {
public:
    Game(Client& client, PACKETS::InitialPacket& startInfo);
 
    
    Game(const Game& orig) = delete;
    Game& operator==(const Game& orig) = delete;
 
    void run();
    ~Game();
    
private:

    GameArea* gameArea_;
    Snake* snake_;
    RenderWindow* window_;

};

#endif /* GAME_H */

