#pragma once
#include "Line.h"

enum class EdgeSide {
	NONE,
	NORTH,
	SOUTH,
	WEST,
	EAST
};

class Edge
{
private:
	EdgeSide edgeSide;
	Line edge;
public:
	// constructors
	Edge();
	Edge(float x, float y, float x1, float y1, EdgeSide edgeSide);

	// setters
	void lenghtenEdge(float x2, float y2);

	// getters
	EdgeSide getEdgeSide();
	Line getEdge();
};

