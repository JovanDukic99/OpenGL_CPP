#include "Block.h"

Block::Block() : matrixPosition(0, 0) {

}

Block::Block(Square bounds, glm::ivec2 matrixPosition) : bounds(bounds), matrixPosition(matrixPosition) {

}

void Block::init(Square bounds, glm::ivec2 matrixPosition) {
	setBounds(bounds);
	setMatrixPosition(matrixPosition);
}

// setters
void Block::setBounds(Square bounds)  {
	this->bounds = bounds;
}

void Block::setMatrixPosition(glm::ivec2 matrixPosition) {
	this->matrixPosition = matrixPosition;
}

// getters
Square Block::getBounds() const {
	return bounds;
}

glm::ivec2 Block::getMatrixPosition() const {
	return matrixPosition;
}
