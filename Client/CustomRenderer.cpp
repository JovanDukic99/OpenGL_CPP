#include "CustomRenderer.h"
#include "EngineConfig.h"

CustomRenderer::CustomRenderer() : offset(0), vertexArray(0), vertexBuffer(0) {

}

CustomRenderer::CustomRenderer(Camera2D& camera2D) : offset(0), vertexArray(0), vertexBuffer(0) {
	init(camera2D);
}

// init
void CustomRenderer::init(Camera2D& camera2D) {
	if (check()) {
		initShaders(camera2D);
		initVertexArray();
	}
}

void CustomRenderer::initShaders(Camera2D& camera2D) {
	shaderProgram.initShaders(camera2D, VISION_VERTEX_PATH, VISION_FRAGMENT_PATH);
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.addAttribute("vertexColor");
	shaderProgram.linkShaders();
}

void CustomRenderer::initVertexArray() {
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);
}

// draw
void CustomRenderer::draw(Point visionCenter, float visionRadius) {
	shaderProgram.use();

	GLint location = shaderProgram.getUniformValueLocation("visionRadius");
	glUniform1f(location, visionRadius);

	location = shaderProgram.getUniformValueLocation("visionCenter");
	glUniform2f(location, visionCenter.getX(), visionCenter.getY());



	shaderProgram.unuse();
}

bool CustomRenderer::check() {
	return vertexArray == 0 && vertexBuffer == 0;
}
