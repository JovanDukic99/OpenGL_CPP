#include "Bullet.h"
#include "ResourceManager.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, std::string texturePath) {
	init(position, direction, speed, texturePath);
}

void Bullet::init(glm::vec2 position, glm::vec2 direction, float speed, std::string texturePath) {
	this->postion = position;
	this->direction = direction;
	this->speed = speed;
	texture = ResourceManager::getTexture(texturePath);
}

void Bullet::draw(SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 posAndSize = glm::vec4(postion.x, postion.y, 10.0f, 10.0f);

	spriteBatch.draw(posAndSize, uv, 0.0f, texture.ID, Color(255, 255, 255, 255));
}

void Bullet::update(){
	postion = postion + direction * speed;
}
