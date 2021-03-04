#pragma once
#include "Square.h"
#include "Light.h"
#include "Graphics.h"
class LightOverlap
{
private:
	Square block;
	Light* light1;
	Light* light2;
public:
	// constructor
	LightOverlap(Square block, Light* light1, Light* light2);

	// operator overload
	bool operator==(const LightOverlap& obj);
	
	// getters
	Square getBlock() const;
	Light* getLight1() const;
	Light* getLight2() const;
};

