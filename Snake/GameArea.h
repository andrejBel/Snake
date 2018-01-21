#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class GameArea
{

private:
	Vector2i size_;
	RectangleShape* area_;
	vector<RectangleShape *> lines_;
	RectangleShape* bonus_;

public:

	GameArea(const int width, const int height, const int spaceBeetweenLines, const Vector2i bonusCoordinates);	

	void draw(RenderWindow& window);

        void setBonusCoordinates(const Vector2f coordinates);
        
	~GameArea();

};