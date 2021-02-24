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
	GLSL_Texture(Square& square, GLTexture texture, glm::vec4 uv, int& offset, std::vector<Vertex>& textureVertices);
	GLSL_Texture(Square& square, GLTexture texture, int& offset, std::vector<Vertex>& textureVertices);
	GLSL_Texture(float x, float y, float width, float height, GLTexture texture, int& offset, std::vector<Vertex>& textureVertices);
	GLSL_Texture(float x, float y, float width, float height, GLTexture texture, glm::vec4 uv, int& offset, std::vector<Vertex>& textureVertices);
	GLuint getTextureID();
private:
	void init(float x, float y, float width, float height, int& offset, std::vector<Vertex>& textureVertices);
	void init(float x, float y, float width, float height, glm::vec4 uv, int& offset, std::vector<Vertex>& textureVertices);
	void generateVertices(float x, float y, float width, float height, std::vector<Vertex>& textureVertices);
	void generateVertices(float x, float y, float width, float height, glm::vec4 uv, std::vector<Vertex>& textureVertices);
};

