#include "Game.h"
#include <algorithm>

Game::Game(int width, int height, const unsigned char numberOfPlayers) :
gameArea_(height, width, CONSTANTS::CHARACTERS::WORLDSFILL),
numberOfPlayers_(numberOfPlayers),
generatorWidth_(0, CONSTANTS::SCREEN_WIDTH - 1),
generatorHeight_(0, CONSTANTS::SCREEN_HEIGHT - 1)
{
    death_.resize(numberOfPlayers_, false);
    win_.resize(numberOfPlayers_, false);
    generateBonusCoordinates();
    for (int id = 0; id < numberOfPlayers_; ++id)
    {
        playerCoordinates_.push_back(vector<Vector2<unsigned char> >());
        bool successGenerate = false;
        int x;
        int y;
        unsigned char smer = generatorWidth_.rand() % 4;
        while (!successGenerate)
        {
            successGenerate = true;
            x = generatorWidth_.rand();
            y = generatorHeight_.rand();
            if (gameArea_(y, x) == CONSTANTS::CHARACTERS::WORLDSFILL)
            {
                gameArea_(y, x) = id;
            }
            else
            {
                successGenerate = false;
            }
        }
        playerCoordinates_[id].push_back(Vector2<unsigned char>(x, y));
        playersInitialCoordinates_.push_back(Vector2<unsigned char>(x, y));
        playersDirections_.push_back(getDirectionFromNumber(smer));
    }
}

void
Game::generateBonusCoordinates()
{
    bool successGenerate = false;
    int x;
    int y;
    while (!successGenerate)
    {
        successGenerate = true;
        x = generatorWidth_.rand();
        y = generatorHeight_.rand();
        char znak = gameArea_(y, x);
        if (gameArea_(y, x) == CONSTANTS::CHARACTERS::WORLDSFILL)
        {
            bonusCoordinates_.x = x;
            bonusCoordinates_.y = y;
            gameArea_(y, x) = CONSTANTS::CHARACTERS::BONUS;
        }
        else
        {
            successGenerate = false;
        }
    }
};

Vector2<char>
Game::getDirectionFromNumber(unsigned char number)
{
    using namespace CONSTANTS::DIRECTIONS;
    if (number == 0)
    {
        return UP;
    }
    if (number == 1)
    {
        return DOWN;
    }
    if (number == 2)
    {
        return LEFT;
    }
    return RIGHT;
}

void
Game::fillInitialPacket(PACKETS::InitialPacket& packet, const int id)
{
    packet.width_ = CONSTANTS::SCREEN_WIDTH;
    packet.height_ = CONSTANTS::SCREEN_HEIGHT;
    packet.numberOfPlayers_ = numberOfPlayers_;
    packet.id_ = id;
    packet.snakeWidth_ = CONSTANTS::SNAKE_WIDTH;
    packet.bonusCoordinates_ = bonusCoordinates_;
    for (int i = 0; i < numberOfPlayers_; i++)
    {
        packet.playerInitialCoordinates[i] = playersInitialCoordinates_[i];
        packet.playerInitialDirection[i] = playersDirections_[i];
    }
}

void
Game::tick(PACKETS::PlayerPacket* playerPaskets, PACKETS::GamePacket& gamePacket)
{
    for (int id = 0; id < numberOfPlayers_; id++)
    {
        nextDirectionFromActual(id, playerPaskets[id].touched_button_, playerPaskets[id].actualDirection_, playersDirections_[id]);
        death_[id] = playerPaskets[id].windowTerminated_;
    }
    int index = 0;
    vector<bool> bonus(numberOfPlayers_, false);
    bool bonusCaught = false;
    for (vector < Vector2<unsigned char>>&body : playerCoordinates_)
    {
        if (!death_[index])
        {
            Vector2<unsigned short> nextPosition(body[0].x + playersDirections_[index].x, body[0].y + playersDirections_[index].y);
            if (nextPosition.x < 0 || nextPosition.y < 0 || nextPosition.x >= CONSTANTS::SCREEN_WIDTH || nextPosition.y >= CONSTANTS::SCREEN_HEIGHT)
            {
                death_[index] = true;
            }
            else
            {
                if (gameArea_(nextPosition.y, nextPosition.x) == CONSTANTS::CHARACTERS::WORLDSFILL)
                {
                    gameArea_(body[body.size() - 1].y, body[body.size() - 1].x) = CONSTANTS::CHARACTERS::WORLDSFILL;
                    for (int i = body.size() - 1; i > 0; i--)
                    {
                        body[i] = body[i - 1];
                    }
                    body[0].x = nextPosition.x;
                    body[0].y = nextPosition.y;
                    gameArea_(body[0].y, body[0].x) = index;
                }
                else if (gameArea_(nextPosition.y, nextPosition.x) == CONSTANTS::CHARACTERS::BONUS)
                {
                    Vector2<unsigned char> next = body[body.size() - 1];
                    body.push_back(next);
                    for (int i = body.size() - 2; i > 0; i--)
                    {
                        body[i] = body[i - 1];
                    }
                    body[0].x = nextPosition.x;
                    body[0].y = nextPosition.y;
                    gameArea_(body[0].y, body[0].x) = index;
                    bonus[index] = true;
                    bonusCaught = true;
                }
                else
                {
                    death_[index] = true;
                }
            }
        }
        index++;
    }
    if (bonusCaught)
    {
        generateBonusCoordinates();
    }

    int numberOfDeaths(0);
    for (int i = 0; i < numberOfPlayers_; i++)
    {
        if (death_[i])
        {
            numberOfDeaths++;
        }
    }

    if ((numberOfPlayers_ - numberOfDeaths) == 1)
    {
        for (int i = 0; i < numberOfPlayers_; i++)
        {
            win_[i] = !death_[i];
        }
    }
    gamePacket.BonusCoordinates_ = bonusCoordinates_;
    for (int i = 0; i < numberOfPlayers_; i++)
    {
        gamePacket.grow_[i] = bonus[i];
        gamePacket.death_[i] = death_[i];
        gamePacket.nextDirections_[i] = playersDirections_[i];
        gamePacket.win_[i] = win_[i];
    }
}

void
Game::nextDirectionFromActual(const int id, const char lastTouched, Vector2<char>& actualDirection, Vector2<char>& nextDirection)
{
    if (lastTouched != CONSTANTS::CHARACTERS::NO_KEY)
    {
        if (lastTouched == CONSTANTS::CHARACTERS::LEFT_KEY)
        {
            if (actualDirection == CONSTANTS::DIRECTIONS::LEFT)
            {
                nextDirection = CONSTANTS::DIRECTIONS::DOWN;
            }
            else if (actualDirection == CONSTANTS::DIRECTIONS::RIGHT)
            {
                nextDirection = CONSTANTS::DIRECTIONS::UP;
            }
            else if (actualDirection == CONSTANTS::DIRECTIONS::DOWN)
            {
                nextDirection = CONSTANTS::DIRECTIONS::RIGHT;
            }
            else
            {
                nextDirection = CONSTANTS::DIRECTIONS::LEFT;
            }
        }
        else if (lastTouched == CONSTANTS::CHARACTERS::RIGHT_KEY)
        {
            if (actualDirection == CONSTANTS::DIRECTIONS::LEFT)
            {
                nextDirection = CONSTANTS::DIRECTIONS::UP;
            }
            else if (actualDirection == CONSTANTS::DIRECTIONS::RIGHT)
            {
                nextDirection = CONSTANTS::DIRECTIONS::DOWN;
            }
            else if (actualDirection == CONSTANTS::DIRECTIONS::DOWN)
            {
                nextDirection = CONSTANTS::DIRECTIONS::LEFT;
            }
            else
            {
                nextDirection = CONSTANTS::DIRECTIONS::RIGHT;
            }
        }
    }
}