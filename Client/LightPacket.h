#pragma once
#include "Square.h"
#include "Light.h"
#include "Graphics.h"
class LightPacket
{
private:
	Light* light;
	Square block;
public:
	// constructor
	LightPacket(Light* light, Square block);

	// operator overload
	bool operator==(const LightPacket& obj);

	// getters
	Light* getLight() const;
	Square getBlock() const;
};

