#pragma once
#include "Line.h"
#include "Point.h"
#include "Square.h"
#include "Circle.h"
#include "GLSL_Object.h"
#include "ShaderProgram.h"
#include <vector>
class Renderer
{
private:
	std::vector<GLSL_Object> geometryObjects;
	std::vector<Vertex> vertices;
	ShaderProgram shaderProgram;
	GLuint vertexArrayID;
	GLuint vertexBufferID;
	int offset;
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
	void begin();
	void end();
private:
	void init();
	void initVertexArray();
	void initShaderProgram(Camera2D& camera);
	void draw();
	void drawGeometry();
	void uploadVertexData();
	void reset();
	bool check();
};


