#pragma once
#include "Node.h"
#include "Point.h"
#include <vector>

class SearchSpace
{
private:
	enum class NodeState {
		NONE,
		ONE_SAME,
		BOTH_SAME,
		DIFFERENT,
	};
private:
	Node** searchSpace;
	Node* startNode;
	Node* finalNode;
	NodeState nodeState;
	int rowNumber;
	int columnNumber;
public:
	// constructors / destructors
	SearchSpace();
	SearchSpace(int rowNumber, int columnNumber);
	SearchSpace(const SearchSpace& searchSpace);
	~SearchSpace();

	// init
	void init(int rowNumber, int columnNumber);

	// reset
	void reset();

	// helper
	bool canStart();

	// operator overloading
	Node* operator[](int index);

	// setters
	void setPredecessor(Node ancestor, Node predecessor);
	void setG(Node node, int g);
	void setH(Node node, int h);
	bool setStartNode(int rowIndex, int columnIndex);
	bool setFinalNode(int rowIndex, int columnIndex);
	bool isPathTheSame();

	// getters
	int getRowNumber();
	int getColumnNumber();
	Node* getStartNode();
	Node* getFinalNode();
	Node** getSearchSpace();
	std::vector<Point> getPath();
private:
	// init
	void initSpace();

	// helper
	bool isBlock(int rowNumber, int columnNumber);
	void checkStartNode(int rowNumber, int columnNumber);
	void checkFinalNode(int rowNumber, int columnNumber);

	// reset
	void resetSpace();
	void resetStartNode();
	void resetFinalNode();

	// setters
	void setRowNumber(int rowNumber);
	void setColumnNumber(int columnNumber);
	void fillSearchSpace(const SearchSpace& object);
};

