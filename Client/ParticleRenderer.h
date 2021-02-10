#pragma once
#include "GeometryObject.h"
#include <GL/glew.h>
#include <vector>

class ParticleRenderer
{
private:
	std::vector<GeometryObject> objects;

public:
	GLuint drawPointLight(float x, float y, float width, float height, Color color);
	void render();
};

