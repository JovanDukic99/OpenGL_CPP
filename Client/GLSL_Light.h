#pragma once
#include "GLSL_Object.h"
#include "Light.h"
#include <vector>
class GLSL_Light : public GLSL_Object
{
public:
	GLSL_Light(float x, float y, float width, float height, const Color& color, int& offset, std::vector<Vertex>& lightVertices);
private:
	void init(float x, float y, float width, float height, const Color& color, int& offset, std::vector<Vertex>& lightVertices);
	void generateVertices(float x, float y, float width, float height, const Color& color, std::vector<Vertex>& lightVertices);
};

