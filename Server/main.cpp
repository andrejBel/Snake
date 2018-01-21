/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: andrej
 *
 * Created on October 31, 2017, 5:28 PM
 */

#include <cstdlib>
#include "Server.h"

using namespace std;

/*
 * 
 */
int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        std::cerr << "usage " << argv[0] << " port_number number_of_players\n";
        return 1;
    }
    bool success = false;
    Server server(std::stoi(argv[1]), std::stoi(argv[2]), success);
    if (success ) 
    {
        cout << "All players succesfully connected\n";
        server.gameLoop();
    } else 
    {
        cout << "Error on connecting\n";
    }
    
    

    std::cout << "Finish\n";
    return 0;
}

