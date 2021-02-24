#include "TileSheet.h"

void TileSheet::init(const GLTexture& texture, const glm::ivec2 dimensions) {
	this->texture = texture;
	this->dimensions = dimensions;
}

glm::vec4 TileSheet::getUVs(int index) {
	int xTile = index % dimensions.x;
	int yTile = index % dimensions.y;

	glm::vec4 uv;

	uv.x = xTile / (float)dimensions.x;
	uv.y = yTile / (float)dimensions.y;
	uv.z = 1.0f / (float)dimensions.x;
	uv.w = 1.0f / (float)dimensions.y;

	return uv;
}
