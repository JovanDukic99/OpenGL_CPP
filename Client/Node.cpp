#include "Node.h"
Node::Node() : g(0), h(0), matrixPosition(0, 0), blockType(BlockType::NONE), visibility(Visibility::NONE), predecessor(nullptr) {
	edges[0] = nullptr;
	edges[1] = nullptr;
	edges[2] = nullptr;
	edges[3] = nullptr;
}

Node::Node(glm::ivec2 matrixPosition, glm::ivec2 worldPosition, glm::vec2 dimensions, BlockType blockType, Visibility visibility) : Square(worldPosition, dimensions), g(0), h(0), matrixPosition(matrixPosition), blockType(blockType), visibility(visibility), predecessor(nullptr) {
	edges[0] = nullptr;
	edges[1] = nullptr;
	edges[2] = nullptr;
	edges[3] = nullptr;
}

void Node::reset() {
	setG(0);
	setH(0);
	setPredecessor(nullptr);
}

bool Node::operator==(const Node& node) {
	return (matrixPosition.y == node.matrixPosition.y) && (matrixPosition.x == node.matrixPosition.x);
}

bool Node::operator!=(const Node& node) {
	return !operator==(node);
}

int Node::getF() {
	return g + h;
}

int Node::getG() {
	return g;
}

int Node::getH() {
	return h;
}

int Node::getRowIndex() {
	return matrixPosition.y;
}

int Node::getColumnIndex() {
	return matrixPosition.x;
}

bool Node::isBlock() {
	return blockType == BlockType::BLOCK;
}

bool Node::isEdge() {
	return blockType == BlockType::EDGE;
}

bool Node::isVisible() {
	return visibility == Visibility::VISIBLE;
}

Node* Node::getPredecessor() {
	return predecessor;
}

Edge* Node::getEdge(EdgeSide edgeSide) {
	switch (edgeSide)
	{
	case EdgeSide::NORTH: {
		return edges[0];
	}
	case EdgeSide::SOUTH: {
		return edges[1];
	}
	case EdgeSide::WEST: {
		return edges[2];
	}
	case EdgeSide::EAST: {
		return edges[3];
	}
	default:
		return nullptr;
	}
}

void Node::setG(int g) {
	this->g = g;
}

void Node::setH(int h) {
	this->h = h;
}

void Node::setRowIndex(int rowIndex) {
	matrixPosition.x = rowIndex;
}

void Node::setColumnIndex(int columnIndex) {
	matrixPosition.y = columnIndex;
}

void Node::setBlockType(BlockType blockType) {
	this->blockType = blockType;
}

void Node::setVisibility(Visibility visibility) {
	this->visibility = visibility;
}

void Node::setPredecessor(Node* predecessor) {
	this->predecessor = predecessor;
}

void Node::addEdge(Edge* edge) {
	EdgeSide edgeSide = edge->getEdgeSide();
	switch (edgeSide)
	{
	case EdgeSide::NORTH :{
		edges[0] = edge;
		break;
	}
	case EdgeSide::SOUTH: {
		edges[1] = edge;
		break;
	}
	case EdgeSide::WEST: {
		edges[2] = edge;
		break;
	}
	case EdgeSide::EAST: {
		edges[3] = edge;
		break;
	}
	default:
		break;
	}
}

std::ostream& operator<<(std::ostream& outputStream, Node& node) {
	return outputStream << "Node [g=" << node.g << " h=" << node.h << ", rowIndex=" << node.matrixPosition.y << ", columnIdex=" << node.matrixPosition.x << ", predecessor="
		<< node.predecessor << ", isBlock=" << (node.blockType == BlockType::BLOCK ? " block" : " edge") << "]" << std::endl;
}
