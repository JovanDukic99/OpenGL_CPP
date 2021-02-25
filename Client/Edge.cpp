#include "Edge.h"

int Edge::nextID = 0;

Edge::Edge() : edgeSide(EdgeSide::NONE), ID(nextID++) {

}

Edge::Edge(float x, float y, float x1, float y1, EdgeSide edgeSide) : edgeSide(edgeSide), ID(nextID++), Line(x, y, x1, y1) {

}

void Edge::lenghtenEdge(float x1, float y1) {
	setP2(glm::vec2(x1, y1));
}

int Edge::getID() {
	return ID;
}

// getters
EdgeSide Edge::getEdgeSide() {
	return edgeSide;
}