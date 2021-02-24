#include "GLSL_Texture.h"

GLSL_Texture::GLSL_Texture(Square& square, GLTexture texture, glm::vec4 uv, int& offset, std::vector<Vertex>& textureVertices) : GLSL_Object(GL_TRIANGLES, 6, offset), textureID(texture.ID) {
	GLSL_Texture(square.getX(), square.getY(), square.getWidth(), square.getHeight(), texture, uv, offset, textureVertices);
}

GLSL_Texture::GLSL_Texture(Square& square, GLTexture texture, int& offset, std::vector<Vertex>& textureVertices) : GLSL_Object(GL_TRIANGLES, 6, offset), textureID(texture.ID) {
	GLSL_Texture(square.getX(), square.getY(), square.getWidth(), square.getHeight(), texture, offset, textureVertices);
}

GLSL_Texture::GLSL_Texture(float x, float y, float width, float height, GLTexture texture, int& offset, std::vector<Vertex>& textureVertices) : GLSL_Object(GL_TRIANGLES, 6, offset), textureID(texture.ID) {
	init(x, y, width, height, offset, textureVertices);
}

GLSL_Texture::GLSL_Texture(float x, float y, float width, float height, GLTexture texture, glm::vec4 uv, int& offset, std::vector<Vertex>& textureVertices) : GLSL_Object(GL_TRIANGLES, 6, offset), textureID(texture.ID) {
	init(x, y, width, height, uv, offset, textureVertices);
}

void GLSL_Texture::init(float x, float y, float width, float height, int& offset, std::vector<Vertex>& textureVertices) {
	generateVertices(x, y, width, height, textureVertices);
	updateOffset(offset);
}

void GLSL_Texture::init(float x, float y, float width, float height, glm::vec4 uv, int& offset, std::vector<Vertex>& textureVertices) {
	generateVertices(x, y, width, height, uv, textureVertices);
	updateOffset(offset);
}

void GLSL_Texture::generateVertices(float x, float y, float width, float height, std::vector<Vertex>& textureVertices) {
	// top-right corner
	textureVertices.emplace_back(x + width, y + height, 1.0f, 1.0f, WHITE);

	// top-left corner
	textureVertices.emplace_back(x, y + height, 0.0f, 1.0f, WHITE);

	// bottom-left corner
	textureVertices.emplace_back(x, y, 0.0f, 0.0f, WHITE);

	// top-right corner
	textureVertices.emplace_back(x + width, y + height, 1.0f, 1.0f, WHITE);

	// bottom-right corner
	textureVertices.emplace_back(x + width, y, 1.0f, 0.0f, WHITE);

	// bottom-left corner
	textureVertices.emplace_back(x, y, 0.0f, 0.0f, WHITE);
}

void GLSL_Texture::generateVertices(float x, float y, float width, float height, glm::vec4 uv, std::vector<Vertex>& textureVertices) {
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

GLuint GLSL_Texture::getTextureID() {
	return textureID;
}

