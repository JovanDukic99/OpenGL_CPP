#include "Light.h"

Light::Light() : Square() {

}

Light::Light(glm::vec2 position, float width, float height, Color color) : Square(position, width, height, color) {

}

Light::Light(float x, float y, float width, float height, Color color) : Square(x, y, width, height, color) {

}
