#include "TextureAtlas.h"

TextureAtlas::TextureAtlas() : texture(), width(0), height(0) {

}

TextureAtlas::TextureAtlas(GLTexture tecture, int width, int height) : texture(texture), width(0), height(0) {

}

// init
void TextureAtlas::init(GLTexture texture, int width, int height) {
	setTexture(texture);
	setWidth(width);
	setHeight(height);
}

// setters
void TextureAtlas::setTexture(GLTexture texture) {
	this->texture = texture;
}

void TextureAtlas::setWidth(int width) {
	this->width = width;
}

void TextureAtlas::setHeight(int height) {
	this->height = height;
}

// private methods
glm::vec4 TextureAtlas::getUV(int index) {
	int xTile = index % width;
	int yTile = index / width;
	
	glm::vec4 uv;

	uv.x = xTile / (float)width;
	uv.y = yTile / (float)height;
	uv.z = 1.0f / (float)width;
	uv.w = 1.0f / (float)height;

	return uv;
}

GLTexture TextureAtlas::getTexture() {
	return texture;
}
