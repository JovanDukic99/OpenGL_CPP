#pragma once
#include "Edge.h"
#include "Square.h"
#include <glm/glm.hpp>
#include <iostream>
// g - how far is node from start point
// h - how far is node from end point

enum class BlockType {
	NONE,
	BLOCK,
	EDGE
};

enum class Visibility {
	NONE,
	VISIBLE,
	INVISIBLE
};

class Node : public Square
{
private:
	int g;
	int h;
	glm::ivec2 matrixPosition;
	Node* predecessor;
	Edge* edges[4];
	BlockType blockType;
	Visibility visibility;
public:
	Node();
	Node(glm::ivec2 matrixPosition, glm::ivec2 worldPosition, glm::vec2 dimensions, BlockType blockType = BlockType::NONE, Visibility visibility = Visibility::NONE);
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
	bool isEdge();
	bool isVisible();
	Node* getPredecessor();
	Edge* getEdge(EdgeSide edgeSide);

	// setters
	void setG(int g);
	void setH(int h);
	void setRowIndex(int rowIndex);
	void setColumnIndex(int columnIndex);
	void setBlockType(BlockType blockType);
	void setVisibility(Visibility visibility);
	void setPredecessor(Node* predecessor);
	void addEdge(Edge* edge);
};

