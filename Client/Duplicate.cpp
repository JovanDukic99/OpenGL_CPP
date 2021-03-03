#include "Duplicate.h"

Duplicate::Duplicate(Square block, Color color, Light* light1, Light* light2) : block(block), color(color), light1(light1), light2(light2) {

}

bool Duplicate::operator==(const Duplicate& obj) {
	return block == obj.block && light1 == obj.light1 && light2 == obj.light2;
}

Square Duplicate::getBlock() const {
	return block;
}

Color Duplicate::getColor() const {
	return color;
}

Light* Duplicate::getLight1() const {
	return light1;
}

Light* Duplicate::getLight2() const {
	return light2;
}
