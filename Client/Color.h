#include <GL/glew.h>

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	Color() : r(0), g(0), b(0), a(0) {

	}

	Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) : r(red), g(green), b(blue), a(alpha) {

	}
};