#include "InputManager.h"

void InputManager::pressKey(unsigned int keyID) {
	// first checks if keyID is in the map, if it is not than create one
	// and assigne it a value
	keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	auto iterator = keyMap.find(keyID);

	// if it found it it will not be equal to end
	if (iterator != keyMap.end()) {
		return iterator->second;
	}

	return false;
}
