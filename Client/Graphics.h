#pragma once
#include <GL/glew.h>

// basic colors
#define RED Color(255,0,0,255)
#define GREEN Color(0,255,0,255)
#define BLUE Color(0,0,255,255)
#define WHITE Color(255,255,255,255)
#define BLACK Color(0,0,0,255)
#define YELLOW Color(255,255,0,255)
#define CYAN Color(0,191,230,255)
#define ORANGE Color(255,140,25,255)
#define VIOLET Color(149,0,179,255)
#define PURPLE Color(255,0,255,255)

class Color {
public:
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
public:
	Color();
	Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
	void setColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
};

class Position {
public:
	float x;
	float y;
public:
	Position();
	Position(float x, float y);
	void setPosition(float x, float y);
};

// UV texture coordinates, range from [0] to [1] (top-right corner <==> [1])
class UV {
public:
	float u;
	float v;
public:
	UV();
	UV(float u, float v);
	void setUV(float u, float v);
};