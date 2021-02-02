#pragma once
#include "GLTexture.h"
#include <string>
class ImageLoader
{
public:
	static GLTexture loadTexture(std::string filePath);
};

