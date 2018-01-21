/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   packet.h
 * Author: andrej
 *
 * Created on November 3, 2017, 4:15 PM
 */

#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <cstring>
#include "CONSTANTS.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace PACKETS 
{

using namespace std;
    
template <typename T>
class serializable
{
public:

	inline string serialize()
	{
		string buf;
		buf.resize(sizeof(T));
		memcpy((void *)buf.c_str(), this, sizeof(T));
		return buf;
	}

     void deserialize(string& buf)
	{
		memcpy(this, buf.c_str(), sizeof(T));
	}
	
};
    
    
struct InitialPacket : serializable<InitialPacket>
{
    unsigned short width_;
    unsigned short height_;
    unsigned char numberOfPlayers_;
    unsigned char id_;
    unsigned char snakeWidth_;
    sf::Vector2<unsigned char> bonusCoordinates_;
    sf::Vector2<unsigned char> playerInitialCoordinates[CONSTANTS::MAX_NUM_OF_PLAYERS];
    sf::Vector2<char> playerInitialDirection[CONSTANTS::MAX_NUM_OF_PLAYERS];
    
    void toString()
        {
            cout <<  "Width of area: " << width_ << endl;
            cout <<  "Height of area: " << height_ << endl;
            cout <<  "Number ofPlayers " << (int) numberOfPlayers_ << endl;
            cout <<  "ID : " << (int)id_ << endl;
            cout << "Width of snake: " << (int)snakeWidth_ << endl;
            cout <<  "Bonus coordinates: " << (int)bonusCoordinates_.x << " " << (int)bonusCoordinates_.y <<endl;
            for (int i = 0; i < numberOfPlayers_; i++)
            {
                cout << "Player " << (int)id_ << " coordinates: " << (int)playerInitialCoordinates[i].x << " " << (int)playerInitialCoordinates[i].y;
            }
            for (int i = 0; i < numberOfPlayers_; i++)
            {
                cout << "Player " << (int)id_ << " direction: " << (int)playerInitialDirection[i].x << " " << (int)playerInitialDirection[i].y;
            }
        }
    
};

struct PlayerPacket :serializable<PlayerPacket>
{
    bool windowTerminated_;
    sf::Vector2<char> actualDirection_;
    char touched_button_;   
};

struct GamePacket: serializable<GamePacket>
{
    sf::Vector2<unsigned char> BonusCoordinates_;
    sf::Vector2<char> nextDirections_[CONSTANTS::MAX_NUM_OF_PLAYERS];
    bool grow_[CONSTANTS::MAX_NUM_OF_PLAYERS];
    bool death_[CONSTANTS::MAX_NUM_OF_PLAYERS];
    bool win_[CONSTANTS::MAX_NUM_OF_PLAYERS];
};

}

#endif /* PACKET_H */

