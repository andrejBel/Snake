#include "GameArea.h"


GameArea::GameArea(const int width, const int height,const int spaceBeetweenLines, const Vector2i bonusCoordinates) :
	size_(width, height),
	area_(new RectangleShape(Vector2f(width, height))),
	bonus_(new RectangleShape(Vector2f(spaceBeetweenLines, spaceBeetweenLines)))
{
	area_->setOutlineColor(Color::White);
	area_->setFillColor(Color::Cyan);
	area_->setPosition(Vector2f(0,0));

	bonus_->setFillColor(Color::Red);
	bonus_->setPosition(Vector2f(bonusCoordinates.x, bonusCoordinates.y));

	int numberOfLinesWidth = width / spaceBeetweenLines - 1;
	int numberOfLinesHeight = height / spaceBeetweenLines - 1;
	int start = spaceBeetweenLines - 1;
	RectangleShape * toAdd = nullptr;
	for (int i = 0; i < numberOfLinesWidth; i++)
	{
		toAdd = new RectangleShape(Vector2f(1, height));
		toAdd->setPosition(start, 0);
		toAdd->setFillColor(Color::Red);
		lines_.push_back(toAdd);
		start += spaceBeetweenLines;
	}
	start = spaceBeetweenLines;
	for (int i = 0; i < numberOfLinesHeight; i++)
	{
		toAdd = new RectangleShape(Vector2f(1, width));
		toAdd->setPosition(0, start);
		toAdd->setFillColor(Color::Red);
		toAdd->rotate(-90);
		lines_.push_back(toAdd);
		start += spaceBeetweenLines;
	}
}



void GameArea::draw(RenderWindow & window)
{
	window.draw(*area_);
	for (RectangleShape* line : lines_)
	{
		window.draw(*line);
	}
	window.draw(*bonus_);
}

void GameArea::setBonusCoordinates(const Vector2f coordinates) 
{
    bonus_->setPosition(coordinates);
}



GameArea::~GameArea()
{
	delete area_;
	area_ = nullptr;
	delete bonus_;
	bonus_ = nullptr;
	for (RectangleShape* line : lines_)
	{
		delete line;
	}
}
