#pragma once
#include "GLSL_Object.h"
#include <glm/glm.hpp>
#include <vector>

class GLSL_Line : public GLSL_Object
{
public:
	GLSL_Line(const glm::vec2& p1, const glm::vec2& p2, const Color& color, int& offset, std::vector<Vertex>& vertices);
private:
	void init(const glm::vec2& p1, const glm::vec2& p2, const Color& color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(const glm::vec2& p1, const glm::vec2& p2, const Color& color, std::vector<Vertex>& vertices);
};

