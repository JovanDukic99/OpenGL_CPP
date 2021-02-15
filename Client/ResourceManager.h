#pragma once
#include "TextureCache.h"
#include <GL/glew.h>
class ResourceManager
{
private:
	static TextureCache textureCache;

public:
	static GLTexture getTexture(std::string texturePath);

};

