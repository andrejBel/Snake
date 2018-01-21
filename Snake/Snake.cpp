#include "Snake.h"
#include "client.h"

#include <iostream>

Snake::Snake(Vector2<unsigned char>* playerCoordinates, Vector2<char>* playerDirections, const int width, const int id, const Keyboard::Key& leftKey, const Keyboard::Key& rightKey, GameArea& area, const int numOfPlayers, Client& client) :
keyboardInput_(CONSTANTS::FREQUENCY_OF_READING_FROM_KEYBOARD, leftKey, rightKey),
area_(area),
id_(id),
numOfPlayers_(numOfPlayers),
client_(client),
ready_(false),
end_(false),
snakeWidth_(width),
score_(0),
windowTerminated_(false)
{
    if (!font_.loadFromFile("arial.ttf"))
    {
        cerr << "ERROR reading font\n";
        throw "ERROR reading font";
    }
    textScore_.setString("0");
    textScore_.setFont(font_);
    textScore_.setCharacterSize(20);
    textScore_.setPosition(0, 0);
    for (int i = 0; i < numOfPlayers_; i++)
    {
        RectangleShape* head = new RectangleShape(Vector2f(width - 1, width - 1));
        head->setPosition(Vector2f(playerCoordinates[i].x * width, playerCoordinates[i].y * width));
        head->setFillColor(CONSTANTS::COLORS[i]);
        gameState_.nextDirections_[i] = playerDirections[i];
        bodies_.push_back(vector<RectangleShape*>());
        bodies_[i].push_back(head);
    }
    //thread_ = std::move(thread([this] () {communicateWithServer();} ) );
    thread_ = std::move(thread(&Snake::communicateWithServer, this));
    
}

void Snake::draw(RenderWindow & window)
{
    for (vector<RectangleShape* >& body : bodies_)
    {
        for (RectangleShape* shape : body)
        {
            window.draw(*shape);
        }
    }
    window.draw(textScore_);
}

void Snake::update()
{
    keyboardInput_.control();

    if (ready_)
    {
        ready_ = false;
        area_.setBonusCoordinates(Vector2f(gameState_.BonusCoordinates_.x * snakeWidth_, gameState_.BonusCoordinates_.y * snakeWidth_));
        keyboardInput_.reset();
        int index = 0;
        for (vector< RectangleShape* >& body_ : bodies_)
        {
            if (!gameState_.death_[index])
            {
                if (gameState_.grow_[index])
                {
                    if (index == id_)
                    {
                        textScore_.setString(to_string(++score_));

                    }
                    RectangleShape * next = new RectangleShape(*body_[body_.size() - 1]);
                    Color c = body_[0]->getFillColor();
                    c.r = 128;
                    next->setFillColor(c);
                    body_.push_back(next);

                    for (int i = body_.size() - 2; i > 0; i--)
                    {
                        body_[i]->setPosition(body_[i - 1]->getPosition());
                    }

                }
                else
                {
                    for (int i = body_.size() - 1; i > 0; i--)
                    {

                        body_[i]->setPosition(body_[i - 1]->getPosition());
                    }
                }
                //cout << " X position: " << body_[0]->getPosition().x << ", Y position: " << body_[0]->getPosition().y << " direction x: " << +gameState_.nextDirections_[index].x << ", direction y: " << + gameState_.nextDirections_[index].y << endl;
                body_[0]->setPosition(body_[0]->getPosition().x + snakeWidth_ * gameState_.nextDirections_[index].x, body_[0]->getPosition().y + snakeWidth_ * gameState_.nextDirections_[index].y);
            }
            index++;
        }
    }

}

void Snake::communicateWithServer()
{
    while (true)
    {
        string message;
        client_.recieveSignal();
        using namespace PACKETS;
        PlayerPacket packet;
        mutex_.lock();
        packet.windowTerminated_ = windowTerminated_;
        packet.actualDirection_ = gameState_.nextDirections_[id_];
        packet.touched_button_ = keyboardInput_.getPressedKey();
        mutex_.unlock();
        message = packet.serialize();
        client_.sendMessage(message);
        client_.getGameState(gameState_);
        if (gameState_.death_[id_] || gameState_.win_[id_])
        {
            if (gameState_.death_[id_])
            {
                textScore_.setString("Game over! Score: " + to_string(score_));
            }
            else
            {
                textScore_.setString("You won! Score: " + to_string(score_));
            }
            end_ = true;
            break;
        }
        ready_ = true;
    }
}

Snake::~Snake()
{
    for (vector<RectangleShape *>& body : bodies_)
    {
        for (RectangleShape* shape : body)
        {
            delete shape;
        }
    }
    thread_.join();
}
