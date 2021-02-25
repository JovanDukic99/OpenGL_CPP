#pragma once
#include "GLSL_Object.h"
#include "GLTexture.h"
#include "Square.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
class GLSL_Texture : public GLSL_Object
{
private:
	GLuint textureID;
public:
	GLSL_Texture(float x, float y, float width, float height, const glm::vec4& uv, const GLTexture& texture, int& offset, std::vector<Vertex>& textureVertices);
	GLuint getTextureID() const;
private:
	void init(float x, float y, float width, float height, const glm::vec4& uv, int& offset, std::vector<Vertex>& textureVertices);
	void generateVertices(float x, float y, float width, float height, const glm::vec4& uv, std::vector<Vertex>& textureVertices);
};

