#include "Animation.h"
#include <iostream>

Animation::Animation() : frameTime(0) {

}

Animation::Animation(std::vector<GLTexture> textures, Uint32 frameTime) : textures(textures), frameTime(frameTime) {

}

// setters
void Animation::addTexture(GLTexture texture) {
	textures.push_back(texture);
}

void Animation::setFrameTime(Uint32 frameTime) {
	this->frameTime = frameTime;
}

// getters
GLTexture Animation::getTexture(Uint32 time) {
	return textures[(time / frameTime) % textures.size()];
}
