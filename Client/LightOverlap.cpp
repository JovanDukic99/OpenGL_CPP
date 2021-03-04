#include "LightOverlap.h"

LightOverlap::LightOverlap(Square block, Light* light1, Light* light2) : block(block), light1(light1), light2(light2) {

}

bool LightOverlap::operator==(const LightOverlap& obj) {
	return (block == obj.block) && (light1 == obj.light2) && (light2 == obj.light1);
}

Square LightOverlap::getBlock() const {
	return block;
}

Light* LightOverlap::getLight1() const {
	return light1;
}

Light* LightOverlap::getLight2() const {
	return light2;
}
