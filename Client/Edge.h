#pragma once
#include "Line.h"

enum class EdgeSide {
	NONE,
	NORTH,
	SOUTH,
	WEST,
	EAST
};

class Edge : public Line
{
private:
	EdgeSide edgeSide;
public:
	// constructors
	Edge();
	Edge(float x, float y, float x1, float y1, EdgeSide edgeSide);
	Edge(glm::vec2 p1, glm::vec2 p2, EdgeSide edgeSide);

	// setters
	void lenghtenEdge(float x1, float y1);

	// getters
	EdgeSide getEdgeSide();
};

