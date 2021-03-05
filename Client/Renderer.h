#pragma once
#include "Line.h"
#include "Point.h"
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"
#include "GLSL_Object.h"
#include "GeometryBase.h"
#include "GLSL_Texture.h"
#include "GLSL_Light.h"
#include "GLSL_Triangle.h"
#include "ShaderProgram.h"
#include "GLTexture.h"
#include "TextureAtlas.h"
#include <vector>
#include <unordered_map>

enum class RenderMode {
	DEFAULT,
	SHADOWS
};

class Renderer
{
private:
	std::vector<GLSL_Object> geometryObjects;
	std::vector<GLSL_Light> lightObjects;
	std::vector<GLSL_Triangle> lightTriangles;
	std::vector<GLSL_Texture> textureObjects;

	std::vector<Vertex> vertices;
	std::vector<Vertex> textureVetrices;

	std::unordered_map<int, std::vector<GLSL_Object>> visibleArea;
	std::unordered_map<int, std::vector<GLSL_Texture>> visibleTextureArea;	
	std::unordered_map<int, std::vector<GLSL_Object>> lightArea;

	std::vector<Light*> lights;

	// non shadow programs
	ShaderProgram geometryProgram;
	ShaderProgram textureProgram;

	// shadow programs
	ShaderProgram visionGeometryProgram;
	ShaderProgram visionTextureProgram;

	GLuint vertexArrays[2];
	GLuint vertexBuffers[2];

	int offset;
	int textureOffset;

	RenderMode mode;
public:
	// constructors
	Renderer();
	Renderer(Camera2D& camera);

	// inits
	void init(Camera2D& camera);

	// ========================== < NON-LIGHT DRAWING > ========================== //

	// draw square
	void drawSquare(float x, float y, float width, float height, Color color = WHITE);
	void drawSquare(Square square, Color color);
	void drawSquare(Square square);

	// draw circle
	void drawCircle(glm::vec2 center, float radius, int segments = SEGMENT_NUMBER, Color color = WHITE);
	void drawCircle(float x, float y, float radius, int segments = SEGMENT_NUMBER, Color color = WHITE);
	void drawCircle(Circle circle, Color color);
	void drawCircle(Circle circle);

	// draw triangle
	void drawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color = WHITE);
	void drawTriangle(Triangle triangle, Color color);
	void drawTriangle(Triangle triangle);

	// draw line
	void drawLine(glm::vec2 p1, glm::vec2 p2, Color color = WHITE);
	void drawLine(float x, float y, float x1, float y1, Color color = WHITE);
	void drawLine(Line line, Color color);
	void drawLine(Line line);

	// draw point
	void drawPoint(glm::vec2 p, Color color = WHITE);
	void drawPoint(float x, float y, Color color = WHITE);
	void drawPoint(Point point, Color color);
	void drawPoint(Point point);
	
	// draw texture
	void drawTexture(float x, float y, float width, float height, GLTexture texture);
	void drawTexture(float x, float y, float width, float height, TextureAtlas textureAtlas, int textureIndex);
	void drawTexture(Square square, GLTexture texture);
	void drawTexture(Square square, TextureAtlas textureAtlas, int textureIndex);

	// ========================== < LIGHT DRAWING > ========================== //

	// draw light mask
	void drawLightMask(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color = WHITE);
	void drawLight(Light* light);
	void drawSquare(Light* light, Square square, Color color);
	void drawTexture(Light* light, Square square, GLTexture texture);

	// being / end
	void begin();
	void end();

	// setters
	void setLights(std::vector<Light*>& lights);
	void setMode(RenderMode mode);
private:
	// init
	void init();
	void initVertexArray();
	void initShaderProgram(Camera2D& camera);

	// draw
	void draw();
	void drawLight();
	void drawGeometry();
	void drawTexture();
	void drawVisibleTexture();
	void drawLightMask();
	void drawVisibleObjects();

	// bind / unbind
	void bindVertexArray(GLuint vertexArrayID);
	void unbindVertexArray();

	// upload
	void uploadTextureUnit();
	void uploadVertexData();

	// reset
	void reset();

	// helper
	bool check();
};


