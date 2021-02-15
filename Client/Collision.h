#pragma once
#include "Square.h"
class Collision
{
public:
	static bool squareCollision(Square s1, Square s2);
private:
	static bool squareOverlap(Square s1, Square s2);
};

