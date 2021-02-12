#include "EntityBase.h"

EntityBase::EntityBase(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {

}

float EntityBase::getX() {
    return x;
}

float EntityBase::getY() {
    return y;
}

float EntityBase::getWidth() {
    return width;
}

float EntityBase::getHeight() {
    return height;
}
