#include "LightPacket.h"

LightPacket::LightPacket(Light* light, Square block) : light(light), block(block) {

}

bool LightPacket::operator==(const LightPacket& obj) {
	return block == obj.block;
}

Light* LightPacket::getLight() const {
	return light;
}

Square LightPacket::getBlock() const {
	return block;
}