#include "Line.h"
#include "Utils.h"

Line::Line() : color(), p1(0.0f, 0.0f), p2(0.0f, 0.0f){

}

Line::Line(glm::vec2 p1, glm::vec2 p2, Color color) : p1(p1), p2(p2), color(color) {

}

Line::Line(float x, float y, float x1, float y1, Color color) : p1(x, y), p2(x1, y1), color(color) {
	
}

// helper
bool Line::contains(glm::vec2 point) {
	return p1 == point || p2 == point;
}

// getters
Color Line::getColor() {
	return color;
}

glm::vec2 Line::getP1() {
	return p1;
}

glm::vec2 Line::getP2() {
	return p2;
}

// setters
void Line::setProperties(glm::vec2 p1, glm::vec2 p2, Color color) {
	setP1(p1);
	setP2(p2);
	setColor(color);
}

void Line::setProperties(float x, float y, float x1, float y1, Color color) {
	setP1(glm::vec2(x, y));
	setP2(glm::vec2(x1, y1));
	setColor(color);
}

void Line::setP1(glm::vec2 p1) {
	this->p1 = p1;
}

void Line::setP2(glm::vec2 p2) {
	this->p2 = p2;
}

void Line::setColor(Color color) {
	this->color = color;
}