#include "Graphics.h"

Color::Color() : r(0), g(0), b(0), a(0) {

}

Color::Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) : r(red), g(green), b(blue), a(alpha) {

}

void Color::setColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
	this->r = red;
	this->g = green;
	this->b = blue;
	this->a = alpha;
}

Position::Position() : x(0.0f), y(0.0f) {
	
}

Position::Position(float x, float y) : x(x), y(y) {

}

void Position::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

UV::UV() : u(0.0f), v(0.0f) {

}

UV::UV(float u, float v) : u(u), v(v) {
	
}

void UV::setUV(float u, float v) {
	this->u = u;
	this->v = v;
}
