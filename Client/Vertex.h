#pragma once
#include <GL/glew.h>

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

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

	// public setters
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
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