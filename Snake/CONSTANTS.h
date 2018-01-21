/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CONSTANTS.h
 * Author: andrej
 *
 * Created on November 1, 2017, 5:43 PM
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics/Color.hpp>
#include <chrono>

namespace CONSTANTS 
{
    const char LEFT_KEY = 'L';
    const char RIGHT_KEY = 'R';
    const char NO_KEY = '-';

    const int MAX_NUM_OF_PLAYERS = 4;
    const int FRAME_LIMIT_RATE = 060;
    
    const int Windows_CLOSE = 5;
    
    const sf::Color COLORS[MAX_NUM_OF_PLAYERS] = { sf::Color::Magenta, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
    
    const std::chrono::milliseconds FREQUENCY_OF_READING_FROM_KEYBOARD = std::chrono::milliseconds(60);
    
    const sf::Int32 END_INTERVAL = 5;
    
}

#endif /* CONSTANTS_H */

