/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientThread.h
 * Author: andrej
 *
 * Created on October 31, 2017, 6:02 PM
 */

#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <iostream>
#include "constants.h"
#include "packet.h"

using namespace std;

class Client {
private:
    const int socketNumber_;
    const int id_;
    bool listen_;

public:

    Client(const int socketNumber, const int id) :
    socketNumber_(socketNumber),
    id_(id),
    listen_(true) {
    }


    Client(const Client& orig) = delete;
    Client& operator=(const Client& right) = delete;

    void send(string& buffer) {
        int n = write(socketNumber_, buffer.c_str(), buffer.size());
        if (n < 0) {
            std::cerr << "ERROR writing to socket\n";
            throw "ERROR writing to socket";
        }
    };

    void recieveSignal() {
        string buffer(10, '\0');
        int n = read(socketNumber_, (void *) buffer.c_str(), 10);
        if (n < 0) {
            std::cerr << "ERROR writing to socket\n";
            throw "ERROR writing to socket";
        }
    }

    void recieve(string& buffer, int size) {
        buffer.resize(size);
        int n = read(socketNumber_, (void *) buffer.c_str(), size);
        if (n < 0) {
            std::cerr << "ERROR writing to socket\n";
            throw "ERROR writing to socket";
        }
    };

    void getPlayerState(PACKETS::PlayerPacket& packet) {
        string buffer = "start";
        send(buffer);
        recieve(buffer, sizeof (PACKETS::PlayerPacket));
        packet.deserialize(buffer);
    }

    void sendGameState(PACKETS::GamePacket& packet) {
        string buf = packet.serialize();
        send(buf);
        if (packet.death_[id_]) {
            listen_ = false;
        }
    }

    bool isListening() {
        return listen_;
    }

    int getId() {
        return id_;
    }

    ~Client() {
        close(socketNumber_);
    }


};

#endif /* CLIENTTHREAD_H */

