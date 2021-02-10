#pragma once
#include "GLTexture.h"
#include "Image.h"
#include <vector>
#include <string>

class ImageLoader
{
public:
	static GLTexture loadTexture(std::string filePath);
	static Image loadImage(std::string filePath);
};

