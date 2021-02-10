#pragma once
#include "GeometryObject.h"
#include <list>

class Renderer
{
private:
	std::list<GeometryObject> objects;

public:
	Renderer();
	GLuint drawLine(float x, float y, float x1, float y1, Color color);
	GLuint drawLine(float x, float y, float x1, float y1, float angle, Color color);
	GLuint drawPoint(float x, float y, Color color);
	GLuint drawSquare(float x, float y, float width, float height, Color color);
	GLuint drawSquare(float x, float y, float width, float height, float angle, Color color);
	GLuint drawCircle(float x, float y, float radius, int segments, Color color);
	GLuint drawLight(float x, float y, float width, float height, Color color);
	void render();
	void clear();
};

