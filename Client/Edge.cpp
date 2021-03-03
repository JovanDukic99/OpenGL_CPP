#include "Edge.h"

Edge::Edge() : edgeSide(EdgeSide::NONE) {

}

Edge::Edge(float x1, float y1, float x2, float y2, EdgeSide edgeSide) : edge(x1, y1, x2, y2), edgeSide(edgeSide) {

}

void Edge::lenghtenEdge(float x2, float y2) {
	edge.setP2(glm::vec2(x2, y2));
}

// getters
EdgeSide Edge::getEdgeSide() {
	return edgeSide;
}

Line Edge::getEdge() {
	return edge;
}
