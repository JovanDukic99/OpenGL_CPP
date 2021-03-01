#include "Renderer.h"
#include "GLSL_Line.h"
#include "GLSL_Point.h"
#include "GLSL_Square.h"
#include "GLSL_Circle.h"
#include "GLSL_Triangle.h"
#include "Light.h"
#include "EngineConfig.h"
#include <TTF/SDL_ttf.h>
#include <GL/glew.h>
#include <iostream>

Renderer::Renderer() : vertexArrays(), vertexBuffers(), offset(0), textureOffset(0), visionRadius(0.0f), visionCenter(0.0f, 0.0f) {

}

Renderer::Renderer(Camera2D& camera) : vertexArrays(), vertexBuffers(), offset(0), textureOffset(0), visionRadius(0.0f), visionCenter(0.0f, 0.0f){
	init();
}

void Renderer::init() {
	initVertexArray();
}

void Renderer::init(Camera2D& camera) {
	if (check()) {
		initVertexArray();
		initShaderProgram(camera);
	}
}

void Renderer::initVertexArray() {
	glGenVertexArrays(2, &vertexArrays[0]);
	glGenBuffers(2, &vertexBuffers[0]);

	// bind shaderProgram buffer
	glBindVertexArray(vertexArrays[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);

	// bind textureProgram buffer
	glBindVertexArray(vertexArrays[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void Renderer::initShaderProgram(Camera2D& camera) {
	// the order of attributes must be the same as order used in shaders
	shaderProgram.initShaders(camera, VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.addAttribute("vertexColor");
	shaderProgram.linkShaders();

	textureProgram.initShaders(camera, TEXTURE_VERTEX_PATH, TEXTURE_FRAGMENT_PATH);
	textureProgram.addAttribute("vertexPosition");
	textureProgram.addAttribute("vertexColor");
	textureProgram.addAttribute("vertexUV");
	textureProgram.linkShaders();

	visionProgram.initShaders(camera, VISION_VERTEX_PATH, VISION_FRAGMENT_PATH);
	visionProgram.addAttribute("vertexPosition");
	visionProgram.addAttribute("vertexColor");
	visionProgram.linkShaders();

	visionTextureProgram.initShaders(camera, VISION_TEXTURE_VERTEX_PATH, VISION_TEXTURE_FRAGMENT_PATH);
	visionTextureProgram.addAttribute("vertexPosition");
	visionTextureProgram.addAttribute("vertexColor");
	visionTextureProgram.addAttribute("vertexUV");
	visionTextureProgram.linkShaders();
}

void Renderer::begin() {
	reset();
}

void Renderer::end() {
	uploadVertexData();
	draw();
}

void Renderer::uploadVertexData() {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, textureVetrices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, textureVetrices.size() * sizeof(Vertex), textureVetrices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::draw() {
	bindVertexArray(vertexArrays[0]);
	// draw light
	shaderProgram.use();

	// additive blending
	glBlendFuncSeparate(GL_ZERO, GL_ZERO, GL_SRC_ALPHA, GL_ZERO);

	drawLight();
	shaderProgram.unuse();




	//glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ZERO);
	glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	//glBlendFunc(GL_DST_ALPHA, GL_ONE);




	// draw geometry
	visionProgram.use();

	/*GLint location = visionProgram.getUniformValueLocation("visionRadius");
	glUniform1f(location, visionRadius);

	location = visionProgram.getUniformValueLocation("visionCenter");
	glUniform2f(location,visionCenter.x, visionCenter.y);*/

	drawGeometry();

	visionProgram.unuse();



	glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bindVertexArray(vertexArrays[1]);
	// draw texture
	visionTextureProgram.use();

	/*location = visionTextureProgram.getUniformValueLocation("visionRadius");
	glUniform1f(location, visionRadius);

	location = visionTextureProgram.getUniformValueLocation("visionCenter");
	glUniform2f(location, visionCenter.x, visionCenter.y);*/

	uploadTextureUnit();
	drawTexture();
	visionTextureProgram.unuse();

	unbindVertexArray();
}

void Renderer::drawGeometry() {
	for (size_t i = 0; i < geometryObjects.size(); i++) {
		GLSL_Object object = geometryObjects[i];
		glDrawArrays(object.getMode(), object.getOffset(), object.getVertexNumber());
	}
}

void Renderer::drawTexture() {
	for (size_t i = 0; i < textureObjects.size(); i++) {
		GLSL_Texture texture = textureObjects[i];
		glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
		glDrawArrays(texture.getMode(), texture.getOffset(), texture.getVertexNumber());
	}
}

void Renderer::drawLight() {
	for (size_t i = 0; i < lightTriangles.size(); i++) {
		GLSL_Triangle triangle = lightTriangles[i];
		glDrawArrays(triangle.getMode(), triangle.getOffset(), triangle.getVertexNumber());
	}
}

void Renderer::bindVertexArray(GLuint vertexArrayID) {
	glBindVertexArray(vertexArrayID);
}

void Renderer::unbindVertexArray() {
	glBindVertexArray(0);
}

void Renderer::uploadTextureUnit() {
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = visionTextureProgram.getUniformValueLocation("asset");
	glUniform1i(textureLocation, 0);
}

// draw square
void Renderer::drawSquare(float x, float y, float width, float height, Color color) {
	geometryObjects.emplace_back(GLSL_Square(x, y, width, height, color, offset, vertices));
}

void Renderer::drawSquare(Square square, Color color) {
	drawSquare(square.getX(), square.getY(), square.getWidth(), square.getHeight(), color);
}

void Renderer::drawSquare(Square square) {
	drawSquare(square.getX(), square.getY(), square.getWidth(), square.getHeight(), square.getColor());
}

// draw circle
void Renderer::drawCircle(float x, float y, float radius, int segments, Color color) {
	geometryObjects.emplace_back(GLSL_Circle(x, y, radius, segments, color, offset, vertices));
}

void Renderer::drawCircle(glm::vec2 center, float radius, int segments, Color color) {
	drawCircle(center.x, center.y, radius, segments, color);
}

void Renderer::drawCircle(Circle circle, Color color) {
	drawCircle(circle.getX(), circle.getY(), circle.getRadius(), circle.getSegments(), color);
}

void Renderer::drawCircle(Circle circle) {
	drawCircle(circle.getX(), circle.getY(), circle.getRadius(), circle.getSegments(), circle.getColor());
}

// draw triangle
void Renderer::drawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color) {
	geometryObjects.emplace_back(GLSL_Triangle(p1, p2, p3, color, offset, vertices));
}

void Renderer::drawTriangle(Triangle triangle, Color color) {
	drawTriangle(triangle.getP1(), triangle.getP2(), triangle.getP3(), color);
}

void Renderer::drawTriangle(Triangle triangle) {
	drawTriangle(triangle.getP1(), triangle.getP2(), triangle.getP3(), triangle.getColor());
}

// draw line
void Renderer::drawLine(glm::vec2 p1, glm::vec2 p2, Color color) {
	geometryObjects.emplace_back(GLSL_Line(p1, p2, color, offset, vertices));
}

void Renderer::drawLine(float x, float y, float x1, float y1, Color color) {
	geometryObjects.emplace_back(GLSL_Line(glm::vec2(x, y), glm::vec2(x1, y1), color, offset, vertices));
}

void Renderer::drawLine(Line line, Color color) {
	drawLine(line.getP1(), line.getP2(), color);
}

void Renderer::drawLine(Line line) {
	drawLine(line.getP1(), line.getP2(), line.getColor());
}

// draw point
void Renderer::drawPoint(glm::vec2 p, Color color) {
	geometryObjects.emplace_back(GLSL_Point(p, color, offset, vertices));
}

void Renderer::drawPoint(float x, float y, Color color) {
	drawPoint(glm::vec2(x, y), color);
}

void Renderer::drawPoint(Point point, Color color) {
	drawPoint(point.getX(), point.getY(), color);
}

void Renderer::drawPoint(Point point) {
	drawPoint(point.getX(), point.getY(), point.getColor());
}

// draw texture
void Renderer::drawTexture(float x, float y, float width, float height, GLTexture texture) {
	textureObjects.emplace_back(x, y, width, height, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture, textureOffset, textureVetrices);
}

void Renderer::drawTexture(Square square, GLTexture texture) {
	drawTexture(square.getX(), square.getY(), square.getWidth(), square.getHeight(), texture);
}

void Renderer::drawTexture(float x, float y, float width, float height, TextureAtlas textureAtlas, int textureIndex) {
	textureObjects.emplace_back(x, y, width, height, textureAtlas.getUV(textureIndex), textureAtlas.getTexture(), textureOffset, textureVetrices);
}

void Renderer::drawTexture(Square square, TextureAtlas textureAtlas, int textureIndex) {
	drawTexture(square.getX(), square.getY(), square.getWidth(), square.getHeight(), textureAtlas, textureIndex);
}

// draw light
void  Renderer::drawLight(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color) {
	lightTriangles.emplace_back(p1, p2, p3, color, offset, vertices);
}

//void Renderer::drawLight(float x, float y, float width, float height, Color color) {
//	lightObject.emplace_back(x, y, width, height, color, lightOffset, lightVertices);
//}
//
//void Renderer::drawLight(Light light, Color color) {
//	drawLight(light.getX(), light.getY(), light.getWidth(), light.getHeight(), color);
//}
//
//void Renderer::drawLight(Light light) {
//	drawLight(light.getX(), light.getY(), light.getWidth(), light.getHeight(), light.getColor());
//}

// reset
void Renderer::reset() {
	vertices.clear();
	textureVetrices.clear();

	geometryObjects.clear();
	textureObjects.clear();
	lightTriangles.clear();

	offset = 0;
	textureOffset = 0;
}

bool Renderer::check() {
	return vertexArrays[0] == 0;
}

// setters
void Renderer::setVision(glm::vec2 visionCenter, float visionRadius) {
	setVisionCenter(visionCenter);
	setVisionRadius(visionRadius);
}

void Renderer::setVisionCenter(glm::vec2 visionCenter) {
	this->visionCenter = visionCenter;
}

void Renderer::setVisionRadius(float visionRadius) {
	this->visionRadius = visionRadius;
}

