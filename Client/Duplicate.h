#pragma once
#include "Square.h"
#include "Light.h"
#include "Graphics.h"
class Duplicate
{
private:
	Square block;
	Color color;
	Light* light1;
	Light* light2;
public:
	// constructor
	Duplicate(Square block, Color color, Light* light1, Light* light2);

	// operator overload
	bool operator==(const Duplicate& obj);
	
	// getters
	Square getBlock() const;
	Color getColor() const;
	Light* getLight1() const;
	Light* getLight2() const;
};

