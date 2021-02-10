#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <string>

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, std::string texturePath);
	void init(glm::vec2 position, glm::vec2 direction, float speed, std::string texturePath);
	void draw(SpriteBatch& spriteBatch);
	void update();
private:
	float speed;
	glm::vec2 postion;
	glm::vec2 direction;
	GLTexture texture;
};

