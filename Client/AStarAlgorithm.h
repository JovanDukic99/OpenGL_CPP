#pragma once
#include "Node.h"
#include "NodeComparator.h"
#include "Point.h"
#include <vector>
#include <queue>
class AStarAlgorithm
{
private:
	Node** searchSpace;
	Node* startNode;
	Node* finalNode;
	std::vector<Node> closedSet;
	std::priority_queue<Node, std::vector<Node>, NodeComparator> openSet;
	int rowNumber;
	int columnNumber;
public:
	AStarAlgorithm();
	AStarAlgorithm(int rowNumber, int columnNumber);
	void init(int rowNumber, int columnNumber);
	void setStartNode(int rowIndex, int columnIndex);
	void setFinalNode(int rowIndex, int columnIndex);
	bool check();
	bool checkNode(int rowIndex, int columnIndex);
	std::vector<Point> search();
	std::vector<Node> getAllNeighbors(Node node);
	void reset();
	Node* operator[](int index);
private:
	void initSpace(int rowNumber, int columnNumber);
	void setRowNumber(int rowNumber);
	void setColumnNumber(int columnNumber);
	void setPredecessor(Node node, Node predecessor);
	void printPath();
	std::vector<Point> getPath();
	bool isNull();
	int manhattanHeuristics(Node node1, Node node2);
};

