/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: andrej
 * 
 * Created on November 10, 2017, 6:52 PM
 */

#include "Game.h"
#include "CONSTANTS.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Game::Game(Client& client, PACKETS::InitialPacket& startInfo):
gameArea_(new GameArea(startInfo.width_ * startInfo.snakeWidth_, startInfo.height_ * startInfo.snakeWidth_, startInfo.snakeWidth_, Vector2i(startInfo.bonusCoordinates_.x * startInfo.snakeWidth_, startInfo.bonusCoordinates_.y * startInfo.snakeWidth_)))
{
    ContextSettings antiAliasing;
    antiAliasing.antialiasingLevel = 8;
    String message = to_string(startInfo.id_);
    snake_ = new Snake(startInfo.playerInitialCoordinates, startInfo.playerInitialDirection, startInfo.snakeWidth_ , startInfo.id_,startInfo.id_ == 0 ? Keyboard::Key::Left : Keyboard::Key::A, startInfo.id_ == 0 ? Keyboard::Key::Right : Keyboard::Key::D, *gameArea_, startInfo.numberOfPlayers_, client);
    //snake_ = new Snake(startInfo.playerInitialCoordinates, startInfo.playerInitialDirection, startInfo.snakeWidth_ , startInfo.id_,Keyboard::Key::Left, Keyboard::Key::Right, *gameArea_, startInfo.numberOfPlayers_, client);
    window_ = new RenderWindow(VideoMode(startInfo.width_ * startInfo.snakeWidth_, startInfo.height_ * startInfo.snakeWidth_, 32), message, Style::Titlebar | Style::Close, antiAliasing);
    window_->setFramerateLimit(CONSTANTS::FRAME_LIMIT_RATE);
}

void
Game::run()
{
    Clock clockTimeOut;
    while (window_->isOpen())
    {
        Event event;
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window_->close();
                snake_->setWindowTerminated();
            }
        }
        if (snake_->isEnd())
        {
            if (clockTimeOut.getElapsedTime().asSeconds() > CONSTANTS::END_INTERVAL) 
            {
                break;
            }
            
        } else 
        {
            snake_->update();
            clockTimeOut.restart();
        }
        

        window_->clear();

        gameArea_->draw(*window_);

        snake_->draw(*window_);
        window_->display();

    }
}

Game::~Game() 
{
    delete window_;
    delete snake_;
    delete gameArea_;
}