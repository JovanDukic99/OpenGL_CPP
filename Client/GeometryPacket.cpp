#include "GeometryPacket.h"

GeometryPacket::GeometryPacket(Light* light, Square block, Color color) : light(light), block(block), color(color) {

}

bool GeometryPacket::operator==(const GeometryPacket& obj) {
	return block == obj.block;
}

Light* GeometryPacket::getLight() const {
	return light;
}

Square GeometryPacket::getBlock() const {
	return block;
}

Color GeometryPacket::getColor() const {
	return color;
}
