#pragma once
#include "ShaderProgram.h"
#include "Camera2D.h"
#include "Point.h"
#include "GLSL_Object.h"
#include "Vertex.h"
#include <vector>
class CustomRenderer
{
private:
	std::vector<GLSL_Object> geometryObjects;
	std::vector<Vertex> geometryVertices;
	int offset;

	ShaderProgram shaderProgram;
	GLuint vertexArray;
	GLuint vertexBuffer;
public:
	// constructors
	CustomRenderer();
	CustomRenderer(Camera2D& camera2D);

	// begin / end
	void begin();
	void end();
private:
	// init
	void init(Camera2D& camera2D);
	void initShaders(Camera2D& camera2D);
	void initVertexArray();

	// draw method
	void draw(Point visionCenter, float visionRadius);

	// helper
	bool check();
};

