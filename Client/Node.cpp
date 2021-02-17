#include "Node.h"
Node::Node() : g(0), h(0), rowIndex(0), columnIndex(0), block(false), predecessor(nullptr) {

}

Node::Node(int rowIndex, int columnIndex, bool block) : g(0), h(0), rowIndex(rowIndex), columnIndex(columnIndex), block(block), predecessor(nullptr) {

}

void Node::reset() {
	setG(0);
	setH(0);
	setPredecessor(nullptr);
}

bool Node::operator==(Node node) {
	return (rowIndex == node.rowIndex) && (columnIndex == node.columnIndex);
}

bool Node::operator!=(Node node) {
	return !operator==(node);
}

int Node::getF() {
	return g << h;
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

std::ostream& operator<<(std::ostream& outputStream, Node& node) {
	return outputStream << "Node [g=" << node.g << " h=" << node.h << ", rowIndex=" << node.rowIndex << ", columnIdex=" << node.columnIndex << ", predecessor="
		<< node.predecessor << ", isBlock=" << node.block << "]" << std::endl;
}
