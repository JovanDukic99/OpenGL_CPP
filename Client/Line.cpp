#include "Line.h"

Line::Line() : points(), color() {

}

Line::Line(float x, float y, float x1, float y1, Color color) {
	setPoints(x, y, x1, y1, color);
}

float* Line::getPoints() {
	return points;
}

Color Line::getColor() {
	return color;
}

void Line::setPoints(float x, float y, float x1, float y1) {
	points[0] = x;
	points[1] = y;
	points[2] = x1;
	points[3] = y1;
}

void Line::setPoints(float x, float y, float x1, float y1, Color color) {
	setPoints(x, y, x1, y1);
	setColor(color);
}

void Line::setColor(Color color) {
	this->color = color;
}
