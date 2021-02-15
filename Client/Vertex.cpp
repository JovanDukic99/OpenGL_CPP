#include "Vertex.h"

Vertex::Vertex() : position(), color(), uv() {

}

Vertex::Vertex(Position position, UV uv, Color color) : position(position), uv(uv), color(color) {

}

Vertex::Vertex(float x, float y, Color color) : position(x, y), uv(1.0f, 1.0f), color(color) {

}

Vertex::Vertex(float x, float y, float u, float v, Color color) : position(x, y), uv(u, v), color(color) {

}

void Vertex::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	color.setColor(r, g, b, a);
}

void Vertex::setColor(Color color) {
	this->color = color;
}

void Vertex::setUV(float u, float v) {
	uv.setUV(u, v);
}

void Vertex::setUV(UV uv) {
	this->uv = uv;
}

void Vertex::setPosition(float x, float y) {
	position.setPosition(x, y);
}

void Vertex::setPosition(Position position) {
	this->position = position;
}

