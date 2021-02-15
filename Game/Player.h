#pragma once
#include <Square.h>
class Player : public Square
{
public:
	Player(float x, float y, float width, float height);
	void update(float x, float y, float deltaTime);
};

