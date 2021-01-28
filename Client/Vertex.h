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

// struct which contains vertex data
struct Vertex {
	Position position;
	Color color;
};