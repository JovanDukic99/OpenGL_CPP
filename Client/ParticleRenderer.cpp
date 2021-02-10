#include "ParticleRenderer.h"
#include "Square.h"
#include "Circle.h"

GLuint ParticleRenderer::drawPointLight(float x, float y, float radius, float segments, Color color) {
	Circle sqare(x, y, radius, segments, color);
	objects.push_back(sqare);
	return sqare.getObjectID();
}

void ParticleRenderer::render() {
	for (GeometryObject object : objects) {
		object.draw();
	}
}
