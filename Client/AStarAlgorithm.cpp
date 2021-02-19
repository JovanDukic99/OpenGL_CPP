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

void AStarAlgorithm::setPredecessor(Node node, Node predecessor) {
	searchSpace[node.getRowIndex()][node.getColumnIndex()].setPredecessor(&searchSpace[predecessor.getRowIndex()][predecessor.getColumnIndex()]);
	searchSpace[node.getRowIndex()][node.getColumnIndex()].setH(node.getH());
	searchSpace[node.getRowIndex()][node.getColumnIndex()].setG(node.getG());
}

void AStarAlgorithm::printPath() {
	Node* temp = finalNode;
	while (temp != nullptr) {
		std::cout << *temp << std::endl;
		temp = temp->getPredecessor();
	}
}

std::vector<Point> AStarAlgorithm::getPath() {
	std::vector<Point> path;
	Node* temp = finalNode;
	while (temp != nullptr) {
		path.emplace_back((float)temp->getColumnIndex(), (float)temp->getRowIndex());
		temp = temp->getPredecessor();
	}
	return path;
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
		startNode = &searchSpace[rowIndex][columnIndex];
	}
}

void AStarAlgorithm::setFinalNode(int rowIndex, int columnIndex) {
	if (checkNode(rowIndex, columnIndex)) {
		finalNode = &searchSpace[rowIndex][columnIndex];
	}
}

bool AStarAlgorithm::checkNode(int rowIndex, int columnIndex) {
	Node node = searchSpace[rowIndex][columnIndex];
	return !node.isBlock();
}

// reset
void AStarAlgorithm::reset() {
	for (int i = 0; i < rowNumber; i++) {
		for (int j = 0; j < columnNumber; j++) {
			searchSpace[i][j].reset();
		}
	}
	startNode = nullptr;
	finalNode = nullptr;
	openSet = std::priority_queue<Node, std::vector<Node>, NodeComparator>();
	closedSet.clear();
}

// search for path
std::vector<Point> AStarAlgorithm::search() {
	if (isNull()) {
		std::cout << "Can't start" << std::endl;
		return std::vector<Point>();
	}
	startNode->setH(manhattanHeuristics(*startNode, *startNode));
	openSet.push(*startNode);

	while (!openSet.empty()) {
		Node node = openSet.top();

		//std::cout << node << std::endl;

		openSet.pop();
		closedSet.push_back(node);

		if (node == *finalNode) {
			std::cout << "Found" << std::endl;
			//printPath();
			return getPath();
		}

		std::vector<Node> neighbors = getAllNeighbors(node);
		for(size_t i = 0; i < neighbors.size(); i++) {
			Node temp = neighbors[i];

			// check if closedSet contains this node
			if (Utils::contains(closedSet, temp)) {
				continue;
			}

			// check if openSet does not contain this node
			if (!Utils::contains(openSet, temp)) {
				openSet.push(temp);
				setPredecessor(temp, node);
			}

			// set predecessor
			
			//temp.setPredecessor(node);
		}
	}

	return std::vector<Point>();
}

std::vector<Node> AStarAlgorithm::getAllNeighbors(Node node) {
	std::vector<Node> neighbors;

	int row = node.getRowIndex();
	int column = node.getColumnIndex();

	// node above
	if ((row - 1 >= 0) && !searchSpace[row - 1][column].isBlock()) {
		Node temp = searchSpace[row - 1][column];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node below
	if ((row + 1 < rowNumber) && !searchSpace[row + 1][column].isBlock()) {
		Node temp = searchSpace[row + 1][column];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node to the left
	if ((column - 1 >= 0) && !searchSpace[row][column - 1].isBlock()) {
		Node temp = searchSpace[row][column - 1];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node to the right
	if ((column + 1 < columnNumber) && !searchSpace[row][column + 1].isBlock()) {
		Node temp = searchSpace[row][column + 1];

		temp.setG(node.getG() + 10);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	//// node at upper rigth corner
	//if ((row - 1 >= 0) && (column + 1 < columnNumber) && !searchSpace[row - 1][column + 1].isBlock()) {
	//	Node temp = searchSpace[row - 1][column + 1];

	//	temp.setG(node.getG() + 14);
	//	temp.setH(manhattanHeuristics(temp, *finalNode));

	//	neighbors.push_back(temp);
	//}

	//// node at bottom right corner
	//if ((row + 1 < rowNumber) && (column + 1 < columnNumber) && !searchSpace[row + 1][column + 1].isBlock()) {
	//	Node temp = searchSpace[row + 1][column + 1];

	//	temp.setG(node.getG() + 14);
	//	temp.setH(manhattanHeuristics(temp, *finalNode));

	//	neighbors.push_back(temp);
	//}

	//// node at upper left corner
	//if ((row - 1 >= 0) && (column - 1 >= 0) && !searchSpace[row - 1][column - 1].isBlock()) {
	//	Node temp = searchSpace[row - 1][column - 1];

	//	temp.setG(node.getG() + 14);
	//	temp.setH(manhattanHeuristics(temp, *finalNode));

	//	neighbors.push_back(temp);
	//}

	//// node at bottom left corner
	//if ((row + 1 < rowNumber) && (column - 1 >= 0) && !searchSpace[row + 1][column - 1].isBlock()) {
	//	Node temp = searchSpace[row + 1][column - 1];

	//	temp.setG(node.getG() + 14);
	//	temp.setH(manhattanHeuristics(temp, *finalNode));

	//	neighbors.push_back(temp);
	//}

	// node at upper right corner
	if ((row - 1 >= 0) && (column + 1 < columnNumber) && !searchSpace[row - 1][column].isBlock() && !searchSpace[row][column + 1].isBlock() && !searchSpace[row - 1][column + 1].isBlock()) {
		Node temp = searchSpace[row - 1][column + 1];

		temp.setG(node.getG() + 14);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node at bottom right corner
	if ((row + 1 < rowNumber) && (column + 1 < columnNumber) && !searchSpace[row + 1][column].isBlock() && !searchSpace[row][column + 1].isBlock() && !searchSpace[row + 1][column + 1].isBlock()) {
		Node temp = searchSpace[row + 1][column + 1];

		temp.setG(node.getG() + 14);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node at upper left corner
	if ((row - 1 >= 0) && (column - 1 >= 0) && !searchSpace[row - 1][column].isBlock() && !searchSpace[row][column - 1].isBlock() && !searchSpace[row - 1][column - 1].isBlock()) {
		Node temp = searchSpace[row - 1][column - 1];

		temp.setG(node.getG() + 14);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	// node at bottom left corner
	if ((row + 1 < rowNumber) && (column - 1 >= 0) && !searchSpace[row + 1][column].isBlock() && !searchSpace[row][column - 1].isBlock() && !searchSpace[row + 1][column - 1].isBlock()) {
		Node temp = searchSpace[row + 1][column - 1];

		temp.setG(node.getG() + 14);
		temp.setH(manhattanHeuristics(temp, *finalNode));

		neighbors.push_back(temp);
	}

	return neighbors;
}

//std::vector<Node*> AStarAlgorithm::getAllNeighbors(Node* node) {
//	std::vector<Node*> neighbors;
//
//	int row = node->getRowIndex();
//	int column = node->getColumnIndex();
//
//	// node above
//	if ((row - 1 >= 0) && !searchSpace[row - 1][column].isBlock()) {
//		Node* temp = &searchSpace[row - 1][column];
//
//		temp->setG(node->getG() + 10);
//		temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//		neighbors.push_back(temp);
//	}
//
//	// node below
//	if ((row + 1 < rowNumber) && !searchSpace[row + 1][column].isBlock()) {
//		Node* temp = &searchSpace[row + 1][column];
//
//		temp->setG(node->getG() + 10);
//		temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//		neighbors.push_back(temp);
//	}
//
//	// node to the left
//	if ((column - 1 >= 0) && !searchSpace[row][column - 1].isBlock()) {
//		Node* temp = &searchSpace[row][column - 1];
//
//		temp->setG(node->getG() + 10);
//		temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//		neighbors.push_back(temp);
//	}
//
//	// node to the right
//	if ((column + 1 < columnNumber) && !searchSpace[row][column + 1].isBlock()) {
//		Node* temp = &searchSpace[row][column + 1];
//
//		temp->setG(node->getG() + 10);
//		temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//		neighbors.push_back(temp);
//	}
//
//	//// node at upper right corner
//	//if ((row - 1 >= 0) && (column + 1 < columnNumber) && !searchSpace[row - 1][column].isBlock() && !searchSpace[row][column + 1].isBlock() && !searchSpace[row - 1][column + 1].isBlock()) {
//	//	Node* temp = &searchSpace[row - 1][column + 1];
//
//	//	temp->setG(node->getG() + 14);
//	//	temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//	//	neighbors.push_back(temp);
//	//}
//
//	//// node at bottom right corner
//	//if ((row + 1 < rowNumber) && (column + 1 < columnNumber) && !searchSpace[row + 1][column].isBlock() && !searchSpace[row][column + 1].isBlock() && !searchSpace[row + 1][column + 1].isBlock()) {
//	//	Node* temp = &searchSpace[row + 1][column + 1];
//
//	//	temp->setG(node->getG() + 14);
//	//	temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//	//	neighbors.push_back(temp);
//	//}
//
//	//// node at upper left corner
//	//if ((row - 1 >= 0) && (column - 1 >= 0) && !searchSpace[row - 1][column].isBlock() && !searchSpace[row][column - 1].isBlock() && !searchSpace[row - 1][column - 1].isBlock()) {
//	//	Node* temp = &searchSpace[row - 1][column - 1];
//
//	//	temp->setG(node->getG() + 14);
//	//	temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//	//	neighbors.push_back(temp);
//	//}
//
//	//// node at bottom left corner
//	//if ((row + 1 < rowNumber) && (column - 1 >= 0) && !searchSpace[row + 1][column].isBlock() && !searchSpace[row][column - 1].isBlock() && !searchSpace[row + 1][column - 1].isBlock()) {
//	//	Node* temp = &searchSpace[row + 1][column - 1];
//
//	//	temp->setG(node->getG() + 14);
//	//	temp->setH(manhattanHeuristics(*temp, *finalNode));
//
//	//	neighbors.push_back(temp);
//	//}
//
//	return neighbors;
//}

int AStarAlgorithm::manhattanHeuristics(Node node1, Node node2) {
	//int x = pow(node2.getRowIndex() - node1.getRowIndex(), 2);
	//int y = pow(node2.getColumnIndex() - node1.getColumnIndex(), 2);
	//return (abs(node2.getRowIndex() - node1.getRowIndex()) + abs(node2.getColumnIndex() - node1.getColumnIndex())) * 10;
	//return sqrt(x + y);
	return std::max(abs(node2.getRowIndex() - node1.getRowIndex()), abs(node2.getColumnIndex() - node1.getColumnIndex())) * 10;
}

Node* AStarAlgorithm::operator[](int index) {
	return searchSpace[index];
}
