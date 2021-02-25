#include "GLSL_Texture.h"

GLSL_Texture::GLSL_Texture(float x, float y, float width, float height, const glm::vec4& uv, const GLTexture& texture, int& offset, std::vector<Vertex>& textureVertices) : GLSL_Object(GL_TRIANGLES, 6, offset), textureID(texture.ID) {
	init(x, y, width, height, uv, offset, textureVertices);
}

void GLSL_Texture::init(float x, float y, float width, float height, const glm::vec4& uv, int& offset, std::vector<Vertex>& textureVertices) {
	generateVertices(x, y, width, height, uv, textureVertices);
	updateOffset(offset);
}

void GLSL_Texture::generateVertices(float x, float y, float width, float height, const glm::vec4& uv, std::vector<Vertex>& textureVertices) {
	// top-right corner
	textureVertices.emplace_back(x + width, y + height, uv.x + uv.z, uv.y + uv.w, WHITE);

	// top-left corner
	textureVertices.emplace_back(x, y + height, uv.x, uv.y + uv.w, WHITE);

	// bottom-left corner
	textureVertices.emplace_back(x, y, uv.x, uv.y, WHITE);

	// top-right corner
	textureVertices.emplace_back(x + width, y + height, uv.x + uv.z, uv.y + uv.w, WHITE);

	// bottom-right corner
	textureVertices.emplace_back(x + width, y, uv.x + uv.z, uv.y, WHITE);

	// bottom-left corner
	textureVertices.emplace_back(x, y, uv.x, uv.y, WHITE);
}

GLuint GLSL_Texture::getTextureID() const {
	return textureID;
}

