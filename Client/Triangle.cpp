#include "Triangle.h"

Triangle::Triangle() : p1(0.0f, 0.0f), p2(0.0f, 0.0f), p3(0.0f, 0.0f), color() {

}

Triangle::Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color) : p1(p1), p2(p2), p3(p3), color(color) {

}

// getters
glm::vec2 Triangle::getP1() const {
	return p1;
}

glm::vec2 Triangle::getP2() const {
	return p2;
}

glm::vec2 Triangle::getP3() const {
	return p3;
}

Color Triangle::getColor() const {
	return color;
}

// setters
void Triangle::setProperties(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color) {
	setP1(p1);
	setP2(p2);
	setP3(p3);
	setColor(color);
}

void Triangle::setP1(glm::vec2 p1) {
	this->p1 = p1;
}

void Triangle::setP2(glm::vec2 p2) {
	this->p2 = p2;
}

void Triangle::setP3(glm::vec2 p3) {
	this->p3 = p3;
}

void Triangle::setColor(Color color) {
	this->color = color;
}
