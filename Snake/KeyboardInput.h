#ifndef KEYBOARINPUT_H
#define KEYBOARINPUT_H

#include "CONSTANTS.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <atomic>

using namespace sf;
using namespace std;

class KeyboardInput {
public:

    KeyboardInput(const std::chrono::milliseconds& readInterval, const Keyboard::Key& leftKey, const Keyboard::Key& rightKey);

    void control();

    KeyboardInput(const KeyboardInput& orig) = delete;
    KeyboardInput& operator=(const KeyboardInput& right) = delete;


    char getPressedKey();

    void reset();
    

private:
    Clock clock_;
    Int32 nextRead_;

    const Keyboard::Key left_;
    const Keyboard::Key right_;

    Keyboard::Key lastTouched_;
    char touched_;
};

#endif /* KEYBOARINPUT_H */

