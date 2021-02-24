#pragma once
#include "GLTexture.h"
#include <glm/glm.hpp>
class TextureAtlas
{
private:
	GLTexture texture;
	int width;
	int height;
public:
	// constructors
	TextureAtlas();
	TextureAtlas(GLTexture tecture, int width, int height);
	// init
	void init(GLTexture tecture, int width, int height);
	// getters
	glm::vec4 getUV(int index);
	GLTexture getTexture();
private:
	// setters
	void setTexture(GLTexture tecture);
	void setWidth(int width);
	void setHeight(int height);
};

