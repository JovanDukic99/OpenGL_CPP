#pragma once
#include "GLTexture.h"
#include <glm/glm.hpp>
class TileSheet
{
private:
	GLTexture texture;
	glm::ivec2 dimensions;
public:
	void init(const GLTexture& texture, const glm::ivec2 dimensions);
	glm::vec4 getUVs(int index);
};

