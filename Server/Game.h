/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: andrej
 *
 * Created on November 4, 2017, 12:04 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Matrix.h"
#include <random>
#include "constants.h"
#include <SFML/Graphics.hpp>
#include "packet.h"
#include <vector>

class Server;


using namespace std;
using namespace sf;


class Game {
    
   
public:

    Game(int width, int height, const unsigned char numberOfPlayers);

    Game(const Game& orig) = delete;
    Game& operator=(const Game& right) = delete;
    
    void fillInitialPacket(PACKETS::InitialPacket& packet, const int id);
    
    void tick(PACKETS::PlayerPacket* playerPaskets, PACKETS::GamePacket& gamePacket);
    
    void print() 
    {
        cout << "------------------------------------------------------\n";
        gameArea_.print();
        cout << "------------------------------------------------------\n";
    }
    
    ~Game() {};

private:

    class Generator 
    {
    private:
        random_device rd;
        mt19937 mt;
        uniform_int_distribution<int> dist;

    public:
        Generator(int min, int max) : rd(), mt( rd()), dist(min, max)
        {
        }

        int rand() {
            return dist(mt);
        }
    };

    //attributes
    
    Matrix<char> gameArea_;
    Generator generatorWidth_;
    Generator generatorHeight_;

    const unsigned char numberOfPlayers_;
    Vector2<unsigned char> bonusCoordinates_;
    vector<Vector2<unsigned char> > playersInitialCoordinates_;
    vector<Vector2<char> > playersDirections_;
    
    vector<vector< Vector2<unsigned char> > > playerCoordinates_;
    
    vector<bool> death_;
    vector<bool> win_;
    

    //functions
    void generateBonusCoordinates();
    Vector2<char> getDirectionFromNumber(unsigned char number);
    void nextDirectionFromActual(const int id, const char lastTouched, Vector2<char>& actualDirection,Vector2<char>& nextDirection);

};


#endif /* GAME_H */

