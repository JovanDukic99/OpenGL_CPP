#pragma once
#include "Line.h"
#include "Point.h"
#include "Square.h"
#include "Circle.h"
#include "GLSL_Object.h"
#include "GLSL_Texture.h"
#include "ShaderProgram.h"
#include "GLTexture.h"
#include <vector>
class Renderer
{
private:
	std::vector<GLSL_Object> geometryObjects;
	std::vector<GLSL_Texture> textureObjects;
	std::vector<Vertex> vertices;
	std::vector<Vertex> textureVetrices;
	ShaderProgram shaderProgram;
	ShaderProgram textureProgram;
	GLuint vertexArrays[2];
	GLuint vertexBuffers[2];
	int offset;
	int textureOffset;
public:
	Renderer();
	Renderer(Camera2D& camera);
	void init(Camera2D& camera);
	void drawSquare(float x, float y, float width, float height, Color color);
	void drawCircle(float x, float y, float radius, int segments, Color color);
	void drawLine(float x, float y, float x1, float y1, Color color);
	void drawPoint(float x, float y, Color color);
	void drawSquare(Square square, Color color);
	void drawCircle(Circle circle, Color color);
	void drawLine(Line line, Color color);
	void drawPoint(Point point, Color color);
	void drawSquare(Square square);
	void drawCircle(Circle circle);
	void drawLine(Line line);
	void drawPoint(Point point);
	void drawTexture(float x, float y, float width, float height, GLTexture texture);
	void drawTexture(Square square, GLTexture texture);
	void begin();
	void end();
private:
	void init();
	void initVertexArray();
	void initShaderProgram(Camera2D& camera);
	void draw();
	void drawGeometry();
	void drawTexture();
	void bindVertexArray(GLuint vertexArrayID);
	void unbindVertexArray();
	void uploadTextureUnit();
	void uploadVertexData();
	void reset();
	bool check();
};


