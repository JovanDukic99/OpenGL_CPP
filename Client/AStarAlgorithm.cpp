#include "AStarAlgorithm.h"
#include "Utils.h"
#include "EngineConfig.h"
#include <cmath>
#include <iostream>
#include <algorithm>

AStarAlgorithm::AStarAlgorithm() : searchSpace(nullptr), algorithmState(AlgorithmState::NONE), searchResult(SearchResult::NONE_SR) {

}

AStarAlgorithm::AStarAlgorithm(SearchSpace* searchSpace) : searchSpace(searchSpace), algorithmState(AlgorithmState::NONE), searchResult(SearchResult::NONE_SR) {

}

// setters
void AStarAlgorithm::setSearchSpace(SearchSpace* searchSpace) {
	this->searchSpace = searchSpace;
}

// getters
bool AStarAlgorithm::isSearching() {
	return algorithmState == AlgorithmState::SEARCHING;
}

// search for path
SearchResult AStarAlgorithm::search() {
	// set AlgorithmState
	setAlgorithmState(AlgorithmState::SEARCHING);

	if (searchSpace->isPathTheSame()) {
		setAlgorithmState(AlgorithmState::NONE);
		return SearchResult::ALREADY_FOUND_SR;
	}

	if (!canStart()) {
		std::cout << "Can't start the algorithm." << std::endl;
		setAlgorithmState(AlgorithmState::NONE);
		return SearchResult::NOT_FOUND_SR;
	}

	START_NODE->setH(manhattanHeuristics(*START_NODE, *START_NODE));
	openSet.push(*START_NODE);

	while (!openSet.empty()) {
		Node node = openSet.top();

		openSet.pop();
		closedSet.push_back(node);

		if (node == *FINAL_NODE) {
			// set AlgorithmState
			setAlgorithmState(AlgorithmState::NONE);
			return SearchResult::FOUND_SR;
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
				setG(temp, temp.getG());
				setH(temp, temp.getH());
			}
		}
	}

	// set AlgorithmState
	setAlgorithmState(AlgorithmState::NONE);

	return SearchResult::NOT_FOUND_SR;
}

void AStarAlgorithm::reset() {
	openSet = std::priority_queue<Node, std::vector<Node>, NodeComparator>();
	closedSet.clear();
	searchSpace->reset();
}

// private functions / setters / helpers
void AStarAlgorithm::setAlgorithmState(AlgorithmState algorithmState) {
	this->algorithmState = algorithmState;
}

void AStarAlgorithm::setPredecessor(Node ancestor, Node predecessor) {
	searchSpace->setPredecessor(ancestor, predecessor);
}

void AStarAlgorithm::setG(Node node, int g) {
	searchSpace->setG(node, g);
}

void AStarAlgorithm::setH(Node node, int h) {
	searchSpace->setH(node, h);
}

std::vector<Node> AStarAlgorithm::getAllNeighbors(Node node) {
	std::vector<Node> neighbors;

	int row = node.getRowIndex();
	int column = node.getColumnIndex();

	// node above
	if ((row - 1 >= 0) && !SEARCH_SPACE[row - 1][column].isBlock()) {
		Node temp = SEARCH_SPACE[row - 1][column];

		temp.setG(node.getG() + HORIZONTAL_VERTICAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

		neighbors.push_back(temp);
	}

	// node below
	if ((row + 1 < SEARCH_SPACE.getRowNumber()) && !SEARCH_SPACE[row + 1][column].isBlock()) {
		Node temp = SEARCH_SPACE[row + 1][column];

		temp.setG(node.getG() + HORIZONTAL_VERTICAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

		neighbors.push_back(temp);
	}

	// node to the left
	if ((column - 1 >= 0) && !SEARCH_SPACE[row][column - 1].isBlock()) {
		Node temp = SEARCH_SPACE[row][column - 1];

		temp.setG(node.getG() + HORIZONTAL_VERTICAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

		neighbors.push_back(temp);
	}

	// node to the right
	if ((column + 1 < SEARCH_SPACE.getColumnNumber()) && !SEARCH_SPACE[row][column + 1].isBlock()) {
		Node temp = SEARCH_SPACE[row][column + 1];

		temp.setG(node.getG() + HORIZONTAL_VERTICAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

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
	if ((row - 1 >= 0) && (column + 1 < SEARCH_SPACE.getColumnNumber()) && !SEARCH_SPACE[row - 1][column].isBlock() && !SEARCH_SPACE[row][column + 1].isBlock() && !SEARCH_SPACE[row - 1][column + 1].isBlock()) {
		Node temp = SEARCH_SPACE[row - 1][column + 1];

		temp.setG(node.getG() + DIAGONAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

		neighbors.push_back(temp);
	}

	// node at bottom right corner
	if ((row + 1 < SEARCH_SPACE.getRowNumber()) && (column + 1 < SEARCH_SPACE.getColumnNumber()) && !SEARCH_SPACE[row + 1][column].isBlock() && !SEARCH_SPACE[row][column + 1].isBlock() && !SEARCH_SPACE[row + 1][column + 1].isBlock()) {
		Node temp = SEARCH_SPACE[row + 1][column + 1];

		temp.setG(node.getG() + DIAGONAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

		neighbors.push_back(temp);
	}

	// node at upper left corner
	if ((row - 1 >= 0) && (column - 1 >= 0) && !SEARCH_SPACE[row - 1][column].isBlock() && !SEARCH_SPACE[row][column - 1].isBlock() && !SEARCH_SPACE[row - 1][column - 1].isBlock()) {
		Node temp = SEARCH_SPACE[row - 1][column - 1];

		temp.setG(node.getG() + DIAGONAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

		neighbors.push_back(temp);
	}

	// node at bottom left corner
	if ((row + 1 < SEARCH_SPACE.getRowNumber()) && (column - 1 >= 0) && !SEARCH_SPACE[row + 1][column].isBlock() && !SEARCH_SPACE[row][column - 1].isBlock() && !SEARCH_SPACE[row + 1][column - 1].isBlock()) {
		Node temp = SEARCH_SPACE[row + 1][column - 1];

		temp.setG(node.getG() + DIAGONAL_COST);
		temp.setH(manhattanHeuristics(temp, *FINAL_NODE));

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

// helpers
bool AStarAlgorithm::canStart() {
	return searchSpace->canStart();
}

int AStarAlgorithm::manhattanHeuristics(Node node1, Node node2) {
	//int x = pow(node2.getRowIndex() - node1.getRowIndex(), 2);
	//int y = pow(node2.getColumnIndex() - node1.getColumnIndex(), 2);
	//return (abs(node2.getRowIndex() - node1.getRowIndex()) + abs(node2.getColumnIndex() - node1.getColumnIndex())) * 10;
	//return sqrt(x + y);
	return std::max(abs(node2.getRowIndex() - node1.getRowIndex()), abs(node2.getColumnIndex() - node1.getColumnIndex())) * 10;
}

