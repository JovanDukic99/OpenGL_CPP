#pragma once
#include "Node.h"
#include "NodeComparator.h"
#include <vector>
#include <queue>
class AStarAlgorithm
{
private:
	Node** searchSpace;
	Node startNode;
	Node finalNode;
	std::vector<Node> closedSet;
	std::priority_queue<Node, std::vector<Node>, NodeComparator> openSet;
public:
	AStarAlgorithm();
	AStarAlgorithm(int rowNumber, int columnNumber);
	void init(int rowNumber, int columnNumber);
	void setStartNode(int rowIndex, int columnIndex);
	void setFinalNode(int rowIndex, int columnIndex);
	bool check();
	bool checkNode(int rowIndex, int columnIndex);
	void search();
	std::vector<Node> getAllNeighbors(Node node);
	void reset();
	Node* operator[](int index);
private:
	void initSpace(int rowNumber, int columnNumber);
	int manhattanHeuristics(Node node1, Node node2);
};

