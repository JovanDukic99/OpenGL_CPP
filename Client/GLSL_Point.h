#pragma once
#include "GLSL_Object.h"
#include "Point.h"
#include <vector>

class GLSL_Point : public GLSL_Object
{
public:
	GLSL_Point(const glm::vec2& p, const Color& color, int& offset, std::vector<Vertex>& vertices);

private:
	void init(const glm::vec2& p, const Color& color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(const glm::vec2& p, const Color& color, std::vector<Vertex>& vertices);
};

