#include "AStarAlgorithm.h"
#include "Utils.h"
#include <cmath>
#include <iostream>
#include <algorithm>
AStarAlgorithm::AStarAlgorithm() : searchSpace(nullptr) {

}

AStarAlgorithm::AStarAlgorithm(int rowNumber, int columnNumber) : searchSpace(nullptr) {
	init(rowNumber, columnNumber);
}

// initialization
void AStarAlgorithm::init(int rowNumber, int columnNumber) {
	if (check()) {
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

bool AStarAlgorithm::check() {
	return searchSpace == nullptr;
}

// setting up nodes
void AStarAlgorithm::setStartNode(int rowIndex, int columnIndex) {
	if (checkNode(rowIndex, columnIndex)) {
		startNode = Node(rowIndex, columnIndex, false);
	}
}

void AStarAlgorithm::setFinalNode(int rowIndex, int columnIndex) {
	if (checkNode(rowIndex, columnIndex)) {
		finalNode = Node(rowIndex, columnIndex, false);
	}
}

bool AStarAlgorithm::checkNode(int rowIndex, int columnIndex) {
	Node node = searchSpace[rowIndex][columnIndex];
	return (node != startNode) && (node != finalNode) && !node.isBlock();
}

// reset
void AStarAlgorithm::reset() {
	for (int i = 0; searchSpace[i] != nullptr; i++) {
		for (int j = 0; &searchSpace[i][j] != nullptr; j++) {
			searchSpace[i][j].reset();
		}
	}
	openSet = std::priority_queue<Node, std::vector<Node>, NodeComparator>();
	closedSet.clear();
}

// search for path
void AStarAlgorithm::search() {
	startNode.setH(manhattanHeuristics(startNode, startNode));
	openSet.push(startNode);

	while (!openSet.empty()) {
		Node node = openSet.top();

		std::cout << node;

		if (node == finalNode) {
			std::cout << "Found";
			return;
		}

		openSet.pop();
		closedSet.push_back(node);

		std::vector<Node> neighbors = getAllNeighbors(node);
		for (int i = 0; i < neighbors.size(); i++) {
			// set predecessor
			neighbors[i].setPredecessor(&node);

			// check if closedSet contains this node
			if (Utils::contains(closedSet, neighbors[i])) {
				continue;
			}

			// check if openSet does not contain this node
		}
	}
}

std::vector<Node> AStarAlgorithm::getAllNeighbors(Node node) {
	std::vector<Node> neighbors;

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
