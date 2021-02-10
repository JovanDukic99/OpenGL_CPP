#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

class InputManager
{
private:
	std::unordered_map<unsigned int, bool> keyMap;
	glm::vec2 mouseCoordinates;
public:
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	glm::vec2 getMouseCoords();
	void setMouseCoords(glm::vec2 mouseCoordinates);

	bool isKeyPressed(unsigned int keyID);
};

