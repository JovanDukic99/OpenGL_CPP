#pragma once
#include "GLTexture.h"
#include <SDL/SDL.h>
#include <vector>
class Animation
{
private:
	std::vector<GLTexture> textures;
	Uint32 frameTime;
public:
	// constructors
	Animation();
	Animation(std::vector<GLTexture> textures, Uint32 frameTime);
	// setters
	void addTexture(GLTexture texture);
	void setFrameTime(Uint32 frameTime);
	// getters
	GLTexture getTexture(Uint32 time);
};

