#include "AStarAlgorithm.h"
#include "Utils.h"
#include <cmath>
#include <iostream>
#include <algorithm>
AStarAlgorithm::AStarAlgorithm() : searchSpace(nullptr), startNode(nullptr), finalNode(nullptr), rowNumber(0), columnNumber(0) {

}

AStarAlgorithm::AStarAlgorithm(int rowNumber, int columnNumber) : searchSpace(nullptr), startNode(nullptr), finalNode(nullptr) {
	init(rowNumber, columnNumber);
}

// initialization
void AStarAlgorithm::init(int rowNumber, int columnNumber) {
	if (check()) {
		setRowNumber(rowNumber);
		setColumnNumber(columnNumber);
		initSpace(rowNumber, columnNumber);
	}
}

void AStarAlgorithm::initSpace(int rowNumber, int columnNumber) {
	// initialize search space
	searchSpace = new Node * [rowNumber];
	for (int i = 0; i < rowNumber; i++) {
		searchSpace[i] = new Node[columnNumber];
	}
}

void AStarAlgorithm::setRowNumber(int rowNumber) {
	this->rowNumber = rowNumber;
}

void AStarAlgorithm::setColumnNumber(int columnNumber) {
	this->columnNumber = columnNumber;
}

void AStarAlgorithm::printPath() {

}

bool AStarAlgorithm::isNull() {
	return (startNode == nullptr) || (finalNode == nullptr);
}

bool AStarAlgorithm::check() {
	return searchSpace == nullptr;
}

// setting up nodes
void AStarAlgorithm::setStartNode(int rowIndex, int columnIndex) {
	if (checkNode(rowIndex, columnIndex)) {
		startNode = new Node(rowIndex, columnIndex, false);
	}
}

void AStarAlgorithm::setFinalNode(int rowIndex, int columnIndex) {
	if (checkNode(rowIndex, columnIndex)) {
		finalNode = new Node(rowIndex, columnIndex, false);
	}
}

bool AStarAlgorithm::checkNode(int rowIndex, int columnIndex) {
	if (isNull()) {
		return true;
	}
	Node node = searchSpace[rowIndex][columnIndex];
	return (node != *startNode) && (node != *finalNode) && !node.isBlock();
}

// reset
void AStarAlgorithm::reset() {
	for (int i = 0; i < rowNumber; i++) {
		for (int j = 0; j < columnNumber; j++) {
			searchSpace[i][j].reset();
		}
	}
	delete startNode;
	delete finalNode;
	openSet.clear();
	closedSet.clear();
}

// search for path
void AStarAlgorithm::search() {
	if (isNull()) {
		std::cout << "Can't start" << std::endl;
		return;
	}
	startNode->setH(manhattanHeuristics(*startNode, *startNode));
	openSet.push(*startNode);

	while (!openSet.empty()) {
		Node node = openSet.pop();

		std::cout << node;

		if (node == *finalNode) {
			std::cout << "Found";
			return;
		}

		closedSet.push_back(node);

		std::vector<Node> neighbors = getAllNeighbors(node);
		for (int i = 0; i < neighbors.size(); i++) {
			Node temp = neighbors[i];
			// set predecessor
			temp.setPredecessor(&node);

			// check if closedSet contains this node
			if (Utils::contains(closedSet, temp)) {
				continue;
			}

			// check if openSet does not contain this node
			if (!openSet.contains(temp)) {
				openSet.push(temp);
			}
		}
	}
}

std::vector<Node> AStarAlgorithm::getAllNeighbors(Node node) {
	std::vector<Node> neighbors;

	int row = node.getRowIndex();
	int column = node.getColumnIndex();

	// node above
	if (row - 1 >= 0 && !searchSpace[row - 1][column].isBlock()) {
		Node temp = searchSpace[row - 1][column];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node below
	if (row + 1 < rowNumber && !searchSpace[row + 1][column].isBlock()) {
		Node temp = searchSpace[row + 1][column];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node to the left
	if (column - 1 >= 0 && !searchSpace[row][column - 1].isBlock()) {
		Node temp = searchSpace[row][column - 1];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node to the rigth
	if (column + 1 < columnNumber && !searchSpace[row][column + 1].isBlock()) {
		Node temp = searchSpace[row][column + 1];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	return neighbors;
}

int AStarAlgorithm::manhattanHeuristics(Node node1, Node node2) {
	int x = pow((node1.getRowIndex() - node2.getRowIndex()), 2);
	int y = pow((node1.getColumnIndex() - node2.getColumnIndex()), 2);
	return sqrt(x + y);
}

Node* AStarAlgorithm::operator[](int index) {
	return searchSpace[index];
}
