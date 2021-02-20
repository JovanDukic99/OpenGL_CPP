#pragma once
#include "SearchSpace.h"
#include "NodeComparator.h"
#include "Point.h"
#include <vector>
#include <queue>

#define SEARCH_SPACE (*searchSpace)
#define START_NODE searchSpace->getStartNode()
#define FINAL_NODE searchSpace->getFinalNode()

enum class AlgorithmState {
	SEARCHING,
	NONE
};

class AStarAlgorithm
{
private:
	SearchSpace* searchSpace;
	AlgorithmState algorithmState;
	std::vector<Node> closedSet;
	std::priority_queue<Node, std::vector<Node>, NodeComparator> openSet;
public:
	// constructors / destructors
	AStarAlgorithm();
	AStarAlgorithm(SearchSpace* searchSpace);

	// setters
	void setSearchSpace(SearchSpace* searchSpace);

	// getters
	bool isSearching();

	// helpers
	bool search();
	void reset();
private:
	// setters
	void setAlgorithmState(AlgorithmState algorithmState);
	void setPredecessor(Node ancestor, Node predecessor);
	void setG(Node node, int g);
	void setH(Node node, int h);

	// getters
	std::vector<Node> getAllNeighbors(Node node);

	// helpers
	bool canStart();

	int manhattanHeuristics(Node node1, Node node2);
};

