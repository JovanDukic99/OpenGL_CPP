#pragma once
#include <GL/glew.h>
#include "Color.h"


struct Position {
	float x;
	float y;
};

// UV texture coordinates, range from [0] to [1] (top-right corner <==> [1])
struct UV {
	float u;
	float v;
};

// struct which contains vertex data
struct Vertex {
	Position position;
	Color color;
	UV uv;

	Vertex() {
		position.x = 0.0;
		position.y = 0.0f;
		uv.u = 0.0f;
		uv.v = 0.0f;
	}

	Vertex(float x, float y, Color color) : color(color) {
		setPosition(x, y);
	}

	// public setters
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setColor(Color color) {
		this->color.r = color.r;
		this->color.g = color.g;
		this->color.b = color.b;
		this->color.a = color.a;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}
};