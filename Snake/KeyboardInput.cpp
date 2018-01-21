#include "KeyboardInput.h"

KeyboardInput::KeyboardInput(const std::chrono::milliseconds& readInterval, const Keyboard::Key& leftKey, const Keyboard::Key& rightKey) :
    nextRead_(readInterval.count()),
    left_(leftKey),
    right_(rightKey),
    lastTouched_(Keyboard::Unknown),
    touched_(CONSTANTS::NO_KEY) {
    }

    void KeyboardInput::control() {
        if (clock_.getElapsedTime().asMilliseconds() > nextRead_) {
            if (lastTouched_ == Keyboard::Key::Unknown) {
                if (Keyboard::isKeyPressed(left_)) {
                    lastTouched_ = left_;
                    touched_ = CONSTANTS::LEFT_KEY;
                } else if (Keyboard::isKeyPressed(right_)) {
                    lastTouched_ = right_;
                    touched_ = CONSTANTS::RIGHT_KEY;
                }
            }
            clock_.restart();
        }
    };

    char KeyboardInput::getPressedKey() {
        return touched_;
    }

    void KeyboardInput::reset() {
        lastTouched_ = Keyboard::Key::Unknown;
        touched_ = CONSTANTS::NO_KEY;
    }
