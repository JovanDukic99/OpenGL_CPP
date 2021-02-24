#include "Node.h"
Node::Node() : g(0), h(0), rowIndex(0), columnIndex(0), block(false), predecessor(nullptr) {
	edges[0] = nullptr;
	edges[1] = nullptr;
	edges[2] = nullptr;
	edges[3] = nullptr;
}

Node::Node(int rowIndex, int columnIndex, bool block) : g(0), h(0), rowIndex(rowIndex), columnIndex(columnIndex), block(block), predecessor(nullptr) {
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
	return (rowIndex == node.rowIndex) && (columnIndex == node.columnIndex);
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
	return rowIndex;
}

int Node::getColumnIndex() {
	return columnIndex;
}

bool Node::isBlock() {
	return block;
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
	this->rowIndex = rowIndex;
}

void Node::setColumnIndex(int columnIndex) {
	this->columnIndex = columnIndex;
}

void Node::setBlock(bool block) {
	this->block = block;
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
	return outputStream << "Node [g=" << node.g << " h=" << node.h << ", rowIndex=" << node.rowIndex << ", columnIdex=" << node.columnIndex << ", predecessor="
		<< node.predecessor << ", isBlock=" << node.block << "]" << std::endl;
}
