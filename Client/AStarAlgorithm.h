#pragma once
#include "SearchSpace.h"
#include "NodeComparator.h"
#include "Point.h"
#include <vector>
#include <queue>

#define SEARCH_SPACE (*searchSpace)
#define START_NODE searchSpace->getStartNode()
#define FINAL_NODE searchSpace->getFinalNode()
#define FOUND SearchResult::FOUND_SR
#define NOT_FOUND SearchResult::NOT_FOUND_SR
#define ALREADY_FOUND SearchResult::ALREADY_FOUND_SR

enum class SearchResult {
		NONE_SR,
		FOUND_SR,
		NOT_FOUND_SR,
		ALREADY_FOUND_SR
	};

class AStarAlgorithm
{
private:
	enum class AlgorithmState {
		SEARCHING,
		NONE
	};
	
private:
	SearchSpace* searchSpace;
	AlgorithmState algorithmState;
	SearchResult searchResult;
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
	SearchResult search();
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

