#pragma once
#include "Edge.h"
#include <iostream>
// g - how far is node from start point
// h - how far is node from end point
class Node
{
private:
	int g;
	int h;
	int rowIndex;
	int columnIndex;
	bool block;
	Node* predecessor;
	Edge* edges[4];
public:
	Node();
	Node(int rowIndex, int columnIndex, bool block = false);
	void reset();

	// operator overloading
	friend std::ostream& operator<<(std::ostream& outputStream, Node& node);
	bool operator==(const Node& node);
	bool operator!=(const Node& node);

	// getters
	int getF();
	int getG();
	int getH();
	int getRowIndex();
	int getColumnIndex();
	bool isBlock();
	Node* getPredecessor();
	Edge* getEdge(EdgeSide edgeSide);

	// setters
	void setG(int g);
	void setH(int h);
	void setRowIndex(int rowIndex);
	void setColumnIndex(int columnIndex);
	void setBlock(bool block);
	void setPredecessor(Node* predecessor);
	void addEdge(Edge* edge);
};

