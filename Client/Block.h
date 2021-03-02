#pragma once
#include "Square.h"
class Block {
private:
	Square bounds;
	glm::ivec2 matrixPosition;
public:
	// constructors
	Block();
	Block(Square bounds, glm::ivec2 matrixPosition);

	// init
	void init(Square bounds, glm::ivec2 matrixPosition);

	// setters
	void setBounds(Square bounds);
	void setMatrixPosition(glm::ivec2 matrixPosition);

	// getterts
	Square getBounds() const;
	glm::ivec2 getMatrixPosition() const;
};

