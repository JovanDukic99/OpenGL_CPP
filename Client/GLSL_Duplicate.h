#pragma once
#include "GLSL_Square.h"
#include "Light.h"
class GLSL_Duplicate
{
private:
	GLSL_Square square;
	Light* light1;
	Light* light2;
public:
	// constructor
	GLSL_Duplicate(GLSL_Square square, Light* light1, Light* light2);
	// getters
	GLSL_Square getGLSL_Square() const;
	Light* getLight1() const;
	Light* getLight2() const;
};

