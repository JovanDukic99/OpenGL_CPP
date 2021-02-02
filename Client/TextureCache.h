#pragma once
#include <map>
#include <string>
#include "GLTexture.h"
class TextureCache
{
private:
	std::map<std::string, GLTexture> textureMap;

public:
	GLTexture getTexture(std::string texturePath);
};

