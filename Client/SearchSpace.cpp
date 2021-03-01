#include "SearchSpace.h"
#include <cstring>

SearchSpace::SearchSpace() : searchSpace(nullptr), startNode(nullptr), finalNode(nullptr), rowNumber(0), columnNumber(0), nodeState(NodeState::NONE), mode(Mode::DEFAULT) {

}

SearchSpace::SearchSpace(int rowNumber, int columnNumber) : startNode(nullptr), finalNode(nullptr), rowNumber(rowNumber), columnNumber(columnNumber), nodeState(NodeState::NONE), mode(Mode::DEFAULT) {
	init(rowNumber, columnNumber);
}

SearchSpace::SearchSpace(const SearchSpace& searchSpace) {
	setRowNumber(searchSpace.rowNumber);
	setColumnNumber(searchSpace.columnNumber);
	init(rowNumber, columnNumber);
	fillSearchSpace(searchSpace);
}

SearchSpace::~SearchSpace() {
	for (int i = 0; i < rowNumber; i++) {
		delete searchSpace[i];
	}
	delete searchSpace;
}

// initialize
void SearchSpace::init(int rowNumber, int columnNumber) {
	setRowNumber(rowNumber);
	setColumnNumber(columnNumber);
	initSpace();
}

// reset
void SearchSpace::reset() {
	resetSpace();
	// resetStartNode();
	// resetFinalNode();
}

// helper
bool SearchSpace::canStart() {
	return startNode != nullptr && finalNode != nullptr;
}

// getters
Node** SearchSpace::getSearchSpace() {
	return searchSpace;
}

int SearchSpace::getRowNumber() {
	return rowNumber;
}

int SearchSpace::getColumnNumber() {
	return columnNumber;
}

Mode SearchSpace::getMode() {
	return mode;
}

Node* SearchSpace::getStartNode() {
	return startNode;
}
Node* SearchSpace::getFinalNode() {
	return finalNode;
}

std::vector<Point> SearchSpace::getPath() {
	std::vector<Point> path;
	Node* temp = finalNode;
	while (temp != nullptr) {
		path.emplace_back((float) temp->getColumnIndex(), (float) temp->getRowIndex());
		temp = temp->getPredecessor();
	}
	return path;
}

// setters
void SearchSpace::setPredecessor(Node ancestor, Node predecessor) {
	searchSpace[ancestor.getRowIndex()][ancestor.getColumnIndex()].setPredecessor(&searchSpace[predecessor.getRowIndex()][predecessor.getColumnIndex()]);
}

void SearchSpace::setG(Node node, int g) {
	searchSpace[node.getRowIndex()][node.getColumnIndex()].setG(g);
}

void SearchSpace::setH(Node node, int h) {
	searchSpace[node.getRowIndex()][node.getColumnIndex()].setH(h);
}

void SearchSpace::setMode(Mode mode) {
	this->mode = mode;
}

void SearchSpace::setVisibility(int rowIndex, int columnIndex, Visibility visibility) {
	searchSpace[rowIndex][columnIndex].setVisibility(visibility);
}

bool SearchSpace::setStartNode(int rowIndex, int columnIndex) {
	checkStartNode(rowIndex, columnIndex);
	if (!isBlock(rowIndex, columnIndex) && !isEdge(rowIndex, columnIndex)) {
		startNode = &searchSpace[rowIndex][columnIndex];
		return true;
	}
	return false;
}

bool SearchSpace::setFinalNode(int rowIndex, int columnIndex) {
	checkFinalNode(rowIndex, columnIndex);
	if (!isBlock(rowIndex, columnIndex) && !isEdge(rowIndex, columnIndex)) {
		finalNode = &searchSpace[rowIndex][columnIndex];
		return true;
	}
	return false;
}

bool SearchSpace::isPathTheSame() {
	return nodeState == NodeState::BOTH_SAME;
}

// operator overloading
Node* SearchSpace::operator[](int index) {
	return searchSpace[index];
}

// private functions : init / reset / helpers / setters
void SearchSpace::initSpace() {
	searchSpace = new Node * [rowNumber];
	for (int i = 0; i < rowNumber; i++) {
		searchSpace[i] = new Node[columnNumber];
	}
}

void SearchSpace::resetSpace() {
	for (int i = 0; i < rowNumber; i++) {
		for (int j = 0; j < columnNumber; j++) {
			searchSpace[i][j].reset();
		}
	}
}

void SearchSpace::resetStartNode() {
	startNode = nullptr;
}
void SearchSpace::resetFinalNode() {
	finalNode = nullptr;
}

// helpers
bool SearchSpace::isBlock(int rowNumber, int columnNumber) {
	return searchSpace[rowNumber][columnNumber].isBlock();
}

bool SearchSpace::isEdge(int rowNumber, int columnNumber) {
	return searchSpace[rowNumber][columnNumber].isEdge();
}

bool SearchSpace::isVisible(int rowIndex, int columnIndex) {
	return searchSpace[rowIndex][columnIndex].isVisible();
}

void SearchSpace::checkStartNode(int rowNumber, int columnNumber) {
	if (startNode == &searchSpace[rowNumber][columnNumber]) {
		nodeState = NodeState::ONE_SAME;
	}
	else {
		nodeState = NodeState::DIFFERENT;
	}
}

void SearchSpace::checkFinalNode(int rowNumber, int columnNumber) {
	if (finalNode == &searchSpace[rowNumber][columnNumber]) {
		nodeState = NodeState::BOTH_SAME;
	}
	else {
		nodeState = NodeState::DIFFERENT;
	}
}

// setters
void SearchSpace::setRowNumber(int rowNumber) {
	this->rowNumber = rowNumber;
}

void SearchSpace::setColumnNumber(int columnNumber) {
	this->columnNumber = columnNumber;
}

void SearchSpace::fillSearchSpace(const SearchSpace& object) {
	for (int i = 0; i < rowNumber; i++) {
		std::memcpy(searchSpace[i], object.searchSpace[i], rowNumber * sizeof(Node));
	}
}

