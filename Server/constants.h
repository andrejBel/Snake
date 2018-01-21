/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   constants.h
 * Author: andrej
 *
 * Created on November 1, 2017, 1:20 PM
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>
#include <chrono>

namespace CONSTANTS
{
    const int SCREEN_WIDTH = 50;
    const int SCREEN_HEIGHT = 40;
    const int SNAKE_WIDTH = 20;
    const unsigned char MAX_NUM_OF_PLAYERS = 4;
    
    const std::chrono::milliseconds SYNCHRONIZE_TIME = std::chrono::milliseconds(400);
    
    namespace CHARACTERS 
    {
        const char BONUS = 'B';
        const char WORLDSFILL = '*';
        
        const char LEFT_KEY = 'L';
        const char RIGHT_KEY = 'R';
        const char NO_KEY = '-';
    }
    
    namespace DIRECTIONS 
    {
        using namespace sf;
        const Vector2<char> UP = Vector2<char>(0,-1); // 0
	const Vector2<char> DOWN = Vector2<char>(0, 1); // 1
	const Vector2<char> LEFT = Vector2<char>(-1, 0); // 2
	const Vector2<char> RIGHT = Vector2<char>(1, 0); // 3
    }
    
    
    
}


#endif

