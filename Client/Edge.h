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
	static int nextID;
	int ID;
	EdgeSide edgeSide;
public:
	// constructors
	Edge();
	Edge(float x, float y, float x1, float y1, EdgeSide edgeSide);

	// setters
	void lenghtenEdge(float x1, float y1);

	// getters
	int getID();
	EdgeSide getEdgeSide();
};

