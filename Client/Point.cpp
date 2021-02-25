#include "Point.h"

Point::Point() : GeometryBase() {

}

Point::Point(glm::vec2 position, Color color) : GeometryBase(position, color) {

}

Point::Point(float x, float y, Color color) : GeometryBase(x, y, color) {

}

bool Point::operator==(const Point& point) {
    return position.x == point.position.x && position.y == point.position.y;
}

bool Point::operator!=(const Point& point) {
    return !operator==(point);
}
