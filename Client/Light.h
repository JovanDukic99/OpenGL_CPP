#pragma once
#include "Square.h"
class Light : public Square
{
public:
	// constructors
	Light();
	Light(float x, float y, float width, float height, Color color = WHITE);
};

