#pragma once
#include "GLSL_Object.h"
#include <vector>
#include <glm/glm.hpp>
class GLSL_Triangle : public GLSL_Object
{
public:
	GLSL_Triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, int& offset, std::vector<Vertex>& vertices);
private:
	void init(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, int& offset, std::vector<Vertex>& vertices);
	void generateVertices(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, std::vector<Vertex>& vertices);
};

