#pragma once
#include "Square.h"
#include "Light.h"
#include "Graphics.h"
class GeometryPacket
{
private:
	Light* light;
	Square block;
	Color color;
public:
	// constructor
	GeometryPacket(Light* light, Square block, Color color);

	// operator overload
	bool operator==(const GeometryPacket& obj);

	// getters
	Light* getLight() const;
	Square getBlock() const;
	Color getColor() const;
};

