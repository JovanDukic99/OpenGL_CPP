#include "Renderer.h"
#include "GLSL_Line.h"
#include "GLSL_Point.h"
#include "GLSL_Square.h"
#include "GLSL_Circle.h"
#include "GLSL_Triangle.h"
#include "Light.h"
#include "EngineConfig.h"
#include "Utils.h"
#include <TTF/SDL_ttf.h>
#include <GL/glew.h>
#include <iostream>

Renderer::Renderer() : vertexArrays(), vertexBuffers(), offset(0), textureOffset(0), mode(RenderMode::DEFAULT) {

}

Renderer::Renderer(Camera2D& camera) : vertexArrays(), vertexBuffers(), offset(0), textureOffset(0), mode(RenderMode::DEFAULT) {
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
	// non shadow shaders
	geometryProgram.initShaders(camera, GEOMETRY_VERTEX_PATH, GEOMETRY_FRAGMENT_PATH);
	geometryProgram.addAttribute("vertexPosition");
	geometryProgram.addAttribute("vertexColor");
	geometryProgram.linkShaders();

	textureProgram.initShaders(camera, TEXTURE_VERTEX_PATH, TEXTURE_FRAGMENT_PATH);
	textureProgram.addAttribute("vertexPosition");
	textureProgram.addAttribute("vertexColor");
	textureProgram.addAttribute("vertexUV");
	textureProgram.linkShaders();

	// shadow programs
	visionGeometryProgram.initShaders(camera, VISION_GEOMETRY_VERTEX_PATH, VISION_GEOMETRY_FRAGMENT_PATH);
	visionGeometryProgram.addAttribute("vertexPosition");
	visionGeometryProgram.addAttribute("vertexColor");
	visionGeometryProgram.linkShaders();

	visionTextureProgram.initShaders(camera, VISION_TEXTURE_VERTEX_PATH, VISION_TEXTURE_FRAGMENT_PATH);
	visionTextureProgram.addAttribute("vertexPosition");
	visionTextureProgram.addAttribute("vertexColor");
	visionTextureProgram.addAttribute("vertexUV");
	visionTextureProgram.linkShaders();

	// multi shadow programs
	multiVisionGeometryProgram.initShaders(camera, MULTI_VISION_GEOMETRY_VERTEX_PATH, MULTI_VISION_GEOMETRY_FRAGMENT_PATH);
	multiVisionGeometryProgram.addAttribute("vertexPosition");
	multiVisionGeometryProgram.addAttribute("vertexColor");
	multiVisionGeometryProgram.linkShaders();

	multiVisionTextureProgram.initShaders(camera, MULTI_VISION_TEXTURE_VERTEX_PATH, MULTI_VISION_TEXTURE_FRAGMENT_PATH);
	multiVisionTextureProgram.addAttribute("vertexPosition");
	multiVisionTextureProgram.addAttribute("vertexColor");
	multiVisionTextureProgram.addAttribute("vertexUV");
	multiVisionTextureProgram.linkShaders();
}

void Renderer::begin() {
	reset();
}

void Renderer::end() {
	filterLightPackets();
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
	if (mode == RenderMode::DEFAULT) {
		bindVertexArray(vertexArrays[0]);

		// draw geometry
		geometryProgram.use();
		drawGeometry();
		geometryProgram.unuse();

		bindVertexArray(vertexArrays[1]);

		// draw texture
		textureProgram.use();
		drawTexture();
		textureProgram.unuse();

		unbindVertexArray();
	}
	else if(mode == RenderMode::SHADOWS) {
		bindVertexArray(vertexArrays[0]);

		// draw light mask
		geometryProgram.use();
		drawLightMask();
		geometryProgram.unuse();

		// draw visible objects
		visionGeometryProgram.use();
		drawVisibleObjects();
		visionGeometryProgram.unuse();

		// draw multi visible objects
		multiVisionGeometryProgram.use();
		drawMultiVisibleObjects();
		multiVisionGeometryProgram.unuse();

		// draw light
		visionGeometryProgram.use();

		GLint radiusLocation = visionGeometryProgram.getUniformValueLocation("visionRadius");
		GLint centerLocation = visionGeometryProgram.getUniformValueLocation("visionCenter");
		GLint intensityLocation = visionGeometryProgram.getUniformValueLocation("intensity");

		for (size_t i = 0; i < lights.size(); i++) {
			Light* light = lights[i];

			glUniform1f(radiusLocation, light->getRadius());
			glUniform1f(intensityLocation, light->getIntensity());
			glUniform2f(centerLocation, light->getSource().x, light->getSource().y);
		}

		drawGeometry();
		visionGeometryProgram.unuse();


		unbindVertexArray();
	}

	//glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//bindVertexArray(vertexArrays[1]);
	//// draw texture
	//visionTextureProgram.use();

	//glUniform1f(visionRadiusLocation, lightRadius);
	//glUniform2f(visionCenterLocation, lightSource.x, lightSource.y);

	//uploadTextureUnit();
	//drawTexture();
	//visionTextureProgram.unuse();
}

void Renderer::drawGeometry() {
	for (size_t i = 0; i < geometryObjects.size(); i++) {
		GLSL_Object object = geometryObjects[i];
		glDrawArrays(object.getMode(), object.getOffset(), object.getVertexNumber());
	}
}

void Renderer::drawTexture() {
	uploadTextureUnit();
	for (size_t i = 0; i < textureObjects.size(); i++) {
		GLSL_Texture texture = textureObjects[i];
		glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
		glDrawArrays(texture.getMode(), texture.getOffset(), texture.getVertexNumber());
	}
}

void Renderer::drawLightMask() {
	// create alpha mask
	glBlendFuncSeparate(GL_ZERO, GL_ZERO, GL_SRC_ALPHA, GL_ZERO);
	for (size_t i = 0; i < lightTriangles.size(); i++) {
		GLSL_Triangle triangle = lightTriangles[i];
		glDrawArrays(triangle.getMode(), triangle.getOffset(), triangle.getVertexNumber());
	}
}

void Renderer::drawVisibleObjects() {
	// use alpah mask
	glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	// draw geometry
	GLint radiusLocation = visionGeometryProgram.getUniformValueLocation("visionRadius");
	GLint centerLocation = visionGeometryProgram.getUniformValueLocation("visionCenter");
	GLint intensityLocation = visionGeometryProgram.getUniformValueLocation("intensity");

	for (size_t i = 0; i < lights.size(); i++) {
		Light* light = lights[i];

		glUniform1f(radiusLocation, light->getRadius());
		glUniform1f(intensityLocation, light->getIntensity());
		glUniform2f(centerLocation, light->getSource().x, light->getSource().y);

		std::vector<GLSL_Object> visibleVector = visibleArea[light->getID()];

		for (size_t i = 0; i < visibleVector.size(); i++) {
			GLSL_Object visibleObject = visibleVector[i];
			glDrawArrays(visibleObject.getMode(), visibleObject.getOffset(), visibleObject.getVertexNumber());
		}
	}
}

void Renderer::drawMultiVisibleObjects() {
	glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	GLint radiusLocation1 = multiVisionGeometryProgram.getUniformValueLocation("visionRadius1");
	GLint radiusLocation2 = multiVisionGeometryProgram.getUniformValueLocation("visionRadius2");

	GLint centerLocation1 = multiVisionGeometryProgram.getUniformValueLocation("visionCenter1");
	GLint centerLocation2 = multiVisionGeometryProgram.getUniformValueLocation("visionCenter2");

	GLint intensityLocation1 = multiVisionGeometryProgram.getUniformValueLocation("intensity1");
	GLint intensityLocation2 = multiVisionGeometryProgram.getUniformValueLocation("intensity2");

	// draw multi visible objects
	for (size_t i = 0; i < glOverlaps.size(); i++) {
		GLSL_LightOverlap glOverlap= glOverlaps[i];
		GLSL_Object object = glOverlap.getGLSL_Square();
		Light* light1 = glOverlap.getLight1();
		Light* light2 = glOverlap.getLight2();

		glUniform1f(intensityLocation1, light1->getIntensity());
		glUniform1f(intensityLocation2, light2->getIntensity());

		glUniform1f(radiusLocation1, light1->getRadius());
		glUniform1f(radiusLocation2, light2->getRadius());

		glUniform2f(centerLocation1, light1->getSource().x, light1->getSource().y);
		glUniform2f(centerLocation2, light2->getSource().x, light2->getSource().y);

		glDrawArrays(object.getMode(), object.getOffset(), object.getVertexNumber());
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

// draw light mask
void  Renderer::drawLightMask(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color) {
	lightTriangles.emplace_back(p1, p2, p3, color, offset, vertices);
}

void Renderer::drawLight(Light* light) {
	Square bounds = light->getBounds();
	lightObjects.emplace_back(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), bounds.getColor(), lightOffset, lightVertices);
}

// draw light objects
void Renderer::drawSquare(Light* light, Square square, Color color) {
	square.setColor(color);
	lightPackets.emplace_back(light, square);
}

void Renderer::filterLightPackets() {
	// extract duplicate blocks, which are being visible by multiple lights
	for (size_t i = 0; i < lightPackets.size(); i++) {

		LightPacket lightPacket = lightPackets[i];
		bool flag = true;

		// we must go from zero because if we don't it will add duplicated block to visibleObjects, (packet == geometryPackets[j]) won't be fulfilled because we can't see elements behind current element
		// but now we have more duplicates then their real number is
		for (size_t j = 0; j < lightPackets.size(); j++) {
			if (i == j) {
				continue;
			}else if (lightPacket == lightPackets[j]) {
				// this is wrong way we have duplicates of overlaps!
				lightOverlaps.emplace_back(lightPacket.getBlock(), lightPacket.getLight(), lightPackets[j].getLight());
				flag = false;
				break;
			}
		}

		if (flag) {
			Square square = lightPacket.getBlock();
			visibleArea[lightPacket.getLight()->getID()].emplace_back(GLSL_Square(square.getX(), square.getY(), square.getWidth(), square.getHeight(), square.getColor(), offset, vertices));
		}
	}

	for (size_t i = 0; i < lightOverlaps.size(); i++) {
		Square square = lightOverlaps[i].getBlock();
		glOverlaps.emplace_back(GLSL_Square(square.getX(), square.getY(), square.getWidth(), square.getHeight(), square.getColor(), offset, vertices), lightOverlaps[i].getLight1(), lightOverlaps[i].getLight2());
	}
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
	lightVertices.clear();
	textureVetrices.clear();

	geometryObjects.clear();
	textureObjects.clear();
	lightTriangles.clear();
	lightObjects.clear();

	offset = 0;
	textureOffset = 0;
	lightOffset = 0;

	if (mode == RenderMode::SHADOWS) {
		for (auto& x : visibleArea) {
			x.second.clear();
		}

		lightPackets.clear();
		lightOverlaps.clear();
		glOverlaps.clear();
	}
}

bool Renderer::check() {
	return vertexArrays[0] == 0;
}

// setters
void Renderer::setLights(std::vector<Light*>& lights) {
	for (size_t i = 0; i < lights.size(); i++) {
		visibleArea[lights[i]->getID()] = std::vector<GLSL_Object>();
	}
	this->lights = lights;
}

void Renderer::setMode(RenderMode mode) {
	this->mode = mode;
}
