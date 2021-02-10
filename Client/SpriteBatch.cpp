#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() : vertexBufferID(0), vertexArrayID(0), sortType(GlyphSortType::NONE) {

}

void SpriteBatch::init() {
	createVertexArray();
}

void SpriteBatch::createRenderBatches() {
	if (glyphs.empty()) {
		return;
	}

	// vertex array
	std::vector<Vertex> vertices;

	// allocate all the memory we need for our array
	vertices.resize(glyphs.size() * 6);

	// instead of resizing vector we can reserve memory to fit our needs
	//vertices.reserve(glyphs.size() * 6);

	int offset = 0;
	int index = 0;

	// creates object of defined type with given values
	renderBatches.emplace_back(0, 6, glyphs[0]->texture);

	vertices[index++] = glyphs[0]->topLeft;
	vertices[index++] = glyphs[0]->topRight;
	vertices[index++] = glyphs[0]->bottomLeft;
	vertices[index++] = glyphs[0]->bottomLeft;
	vertices[index++] = glyphs[0]->bottomRight;
	vertices[index++] = glyphs[0]->topRight;
	offset += 6;
	

	for (int i = 1; i < glyphs.size(); i++) {
		if (glyphs[i]->texture != glyphs[i - 1]->texture) {
			renderBatches.emplace_back(offset, 6, glyphs[i]->texture);
		}
		else {
			renderBatches.back().numVertices += 6;
		}
		vertices[index++] = glyphs[i]->topLeft;
		vertices[index++] = glyphs[i]->topRight;
		vertices[index++] = glyphs[i]->bottomLeft;
		vertices[index++] = glyphs[i]->bottomLeft;
		vertices[index++] = glyphs[i]->bottomRight;
		vertices[index++] = glyphs[i]->topRight;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray() {
	if (vertexArrayID == 0) {
		glGenVertexArrays(1, &vertexArrayID);
	}

	glBindVertexArray(vertexArrayID);
	
	if (vertexBufferID == 0) {
		glGenBuffers(1, &vertexBufferID);
	}

	// whenever we rebind VertexArray automatically bind buffer below
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	// automatically disable anything what was enabled above
	glBindVertexArray(0);
}

void SpriteBatch::begin(GlyphSortType sortType) {
	this->sortType = sortType;
	renderBatches.clear();
	glyphs.clear();
}

void SpriteBatch::end() {
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::sortGlyphs() {
	// elements with the same value are in the same order
	switch (sortType)
	{
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(glyphs.begin(), glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
		break;
	default:
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, const GLuint& texture, const Color& color) {
	Glyph* glyph = new Glyph();
	glyph->texture = texture;
	glyph->depth = depth;

	glyph->topLeft.color = color;
	glyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	glyph->bottomLeft.color = color;
	glyph->bottomLeft.setPosition(destRect.x, destRect.y);
	glyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	glyph->topRight.color = color;
	glyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	glyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	glyph->bottomRight.color = color;
	glyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	glyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	glyphs.push_back(glyph);
}

void SpriteBatch::renderBatch() {
	glBindVertexArray(vertexArrayID);
	for (int i = 0; i < renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}


