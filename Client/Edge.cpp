#include "Edge.h"

Edge::Edge() : edgeSide(EdgeSide::NONE) {

}

Edge::Edge(float x, float y, float x1, float y1, EdgeSide edgeSide) : Line(x, y, x1, y1), edgeSide(edgeSide) {

}

Edge::Edge(glm::vec2 p1, glm::vec2 p2, EdgeSide edgeSide) : Line(p1, p2), edgeSide(edgeSide)  {

}

void Edge::lenghtenEdge(float x1, float y1) {
	setP2(glm::vec2(x1, y1));
}

// getters
EdgeSide Edge::getEdgeSide() {
	return edgeSide;
}