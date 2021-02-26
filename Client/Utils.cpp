#include "Utils.h"
#include "ImageLoader.h"
#include "Node.h"
#include <iostream>

void Utils::loadMap(std::string filePath, std::vector<Square>& blocks, float unitWidth, float unitHeight) {
	Image image = ImageLoader::loadImage(filePath);

	float mapHeight = image.getHeight() * unitHeight;

	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			int pixel = image[i][j];

			int r = (pixel >> 24) & 0xff;
			int g = (pixel >> 16) & 0xff;
			int b = (pixel >> 8) & 0xff;
			int a = pixel & 0xff;

			if (r == 0 && g == 0 && b == 0 && a == 255) {
				float y = mapHeight - unitHeight * (i + 1);
				float x = j * unitWidth;
				blocks.emplace_back(x, y, unitWidth, unitHeight);
			}
		}
	}
}

void Utils::loadMASP(std::string filePath, std::vector<Square>& blocks, SearchSpace& searchSpace, float unitWidth, float unitHeight) {
	Image image = ImageLoader::loadImage(filePath);

	float mapHeight = image.getHeight() * unitHeight;

	searchSpace.init(image.getHeight(), image.getWidth());

	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			int pixel = image[i][j];

			int r = (pixel >> 24) & 0xff;
			int g = (pixel >> 16) & 0xff;
			int b = (pixel >> 8) & 0xff;
			int a = pixel & 0xff;

			if (r == 0 && g == 0 && b == 0 && a == 255) {
				float y = mapHeight - unitHeight * (i + 1);
				float x = j * unitWidth;
				blocks.emplace_back(x, y, unitWidth, unitHeight);
				searchSpace[i][j] = Node(i, j, true);
			}
			else {
				searchSpace[i][j] = Node(i, j, false);
			}
		}
	}
}

std::vector<Point> Utils::convertToSquarePath(std::vector<Point> points, float mapHeight, float unitWidth, float unitHeight) {
	std::vector<Point> playerPath;
	playerPath.resize(points.size());

	for (size_t i = 0; i < points.size(); i++) {
		playerPath[i].setX(points[i].getX() * unitWidth);
		playerPath[i].setY(mapHeight - (points[i].getY() * unitHeight) - unitHeight);
	}

	return playerPath;
}

std::vector<Point>& Utils::convertToPlayerPath(std::vector<Point>& points, float endX, float endY) {
	size_t size = points.size();
	points[size - 1].setX(endX);
	points[size - 1].setY(endY);
	return points;
}

void Utils::createEdges(SearchSpace& searchSpace, std::vector<Square>& blocks, std::vector<Edge*>& edges, float mapHeight, float unitWidth, float unitHeight) {
	for (size_t i = 0; i < blocks.size(); i++) {
		Square& block = blocks[i];

		float x = block.getX();
		float y = block.getY();
		
		int row = (mapHeight - y - unitHeight) / unitHeight;
		int column = x / unitWidth;

		float width = block.getWidth();
		float height = block.getHeight();

		// ================================== NORTH EDGE ===================================== 
		// if there is node on top side than skip this edge
		if (!((row - 1 >= 0) && searchSpace.isBlock(row - 1, column))) {
			// node from left, if it exists lenghten the edge, otherwise create one
			if (column - 1 >= 0 && searchSpace.isBlock(row, column - 1)) {
				Edge* edge = searchSpace[row][column - 1].getEdge(EdgeSide::NORTH);
				if (edge != nullptr) {
					edge->lenghtenEdge(x + width, y + height);
					searchSpace[row][column].addEdge(edge);
				}
				else {
					Edge* edge = new Edge(x, y + height, x + width, y + height, EdgeSide::NORTH);
					searchSpace[row][column].addEdge(edge);
					edges.push_back(edge);
				}
			}
			else {
				Edge* edge = new Edge(x, y + height, x + width, y + height, EdgeSide::NORTH);
				searchSpace[row][column].addEdge(edge);
				edges.push_back(edge);
			}
		}
		// ================================== SOUTH EDGE =====================================
		// if there is node on top bottom than skip this edge
		if (!((row + 1 < searchSpace.getRowNumber()) && searchSpace.isBlock(row + 1, column))) {
			// node from left
			if (column - 1 >= 0 && searchSpace.isBlock(row, column - 1)) {
				Edge* edge = searchSpace[row][column - 1].getEdge(EdgeSide::SOUTH);
				if (edge != nullptr) {
					edge->lenghtenEdge(x + width, y);
					searchSpace[row][column].addEdge(edge);
				}
				else {
					// if node from the left do not have south edge than create one
					Edge* edge = new Edge(x, y, x + width, y, EdgeSide::SOUTH);
					searchSpace[row][column].addEdge(edge);
					edges.push_back(edge);
				}
			}
			else {
				Edge* edge = new Edge(x, y, x + width, y, EdgeSide::SOUTH);
				searchSpace[row][column].addEdge(edge);
				edges.push_back(edge);
			}
		}
		// ================================== WEST EDGE =====================================
		// if there is node on left side than skip this edge
		if (!((column - 1 >= 0) && searchSpace.isBlock(row, column - 1))) {
			// node from top
			if (row - 1 >= 0 && searchSpace.isBlock(row - 1, column)) {
				Edge* edge = searchSpace[row - 1][column].getEdge(EdgeSide::WEST);
				if (edge != nullptr) {
					edge->lenghtenEdge(x, y);
					searchSpace[row][column].addEdge(edge);
				}
				else {
					Edge* edge = new Edge(x, y + height, x, y, EdgeSide::WEST);
					searchSpace[row][column].addEdge(edge);
					edges.push_back(edge);
				}
			}
			else {
				Edge* edge = new Edge(x, y + height, x, y, EdgeSide::WEST);
				searchSpace[row][column].addEdge(edge);
				edges.push_back(edge);
			}
		}
		// ================================== EAST EDGE =====================================
		// if there is node on right side than skip this edge
		if (!((column + 1 < searchSpace.getColumnNumber()) && searchSpace.isBlock(row, column + 1))) {
			// node from top
			if (row - 1 >= 0 && searchSpace.isBlock(row - 1, column)) {
				Edge* edge = searchSpace[row - 1][column].getEdge(EdgeSide::EAST);
				if (edge != nullptr) {
					edge->lenghtenEdge(x + width, y);
					searchSpace[row][column].addEdge(edge);
				}
				else {
					Edge* edge = new Edge(x + width, y + height, x + width, y, EdgeSide::EAST);
					searchSpace[row][column].addEdge(edge);
					edges.push_back(edge);
				}
			}
			else {
				Edge* edge = new Edge(x + width, y + height, x + width, y, EdgeSide::EAST);
				searchSpace[row][column].addEdge(edge);
				edges.push_back(edge);
			}
		}
	}
}

void Utils::createEdgePoints(std::vector<Edge*>& edges, std::vector<glm::vec2>& edgePoints) {
	// filter points => eliminate same points
	for (size_t i = 0; i < edges.size(); i++) {
		Edge* edge = edges[i];
		glm::vec2 p1 = edge->getP1();
		glm::vec2 p2 = edge->getP2();
		if (!contains(edgePoints, p1)) {
			edgePoints.push_back(p1);
		}
		if (!contains(edgePoints, p2)) {
			edgePoints.push_back(p2);
		}
	}
}

void Utils::rayTracing(std::vector<Edge*>& edges, std::vector<glm::vec2>& edgePoints, std::vector<glm::vec2>& lightPoints, glm::vec2 p) {
	for (size_t i = 0; i < edgePoints.size(); i++) {
		glm::vec2 point = edgePoints[i];

		Line line1(point, p);

		float minDistance = INFINITY;
		glm::vec2 closestPoint(0.0f, 0.0f);

		for (size_t j = 0; j < edges.size(); j++) {
			Edge* line2 = edges[j];

			bool check = false;

			glm::vec2 intersection = lineIntersection(line1.getP1(), line1.getP2(), line2->getP1(), line2->getP2(), &check);

			if (check) {
				float distance = glm::length(intersection - p);

				if (distance < minDistance) {
					minDistance = distance;
					closestPoint = intersection;
				}

			}

		}

		lightPoints.emplace_back(closestPoint.x, closestPoint.y);
	}
}
glm::vec2 Utils::lineIntersection(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, bool* check) {
	glm::vec2 r = b - a;
	glm::vec2 s = d - c;

	float scalar = r.x * s.y - r.y * s.x;
	float u = ((c.x - a.x) * r.y - (c.y - a.y) * r.x) / scalar;
	float t = ((c.x - a.x) * s.y - (c.y - a.y) * s.x) / scalar;

	if ((0.0f <= u) && (u <= 1.0f) && (0.0f <= t) && (t <= 1.0f)) {
		*check = true;
		return glm::vec2(a + t * r);
	}
	else {
		*check = false;
		return glm::vec2(0.0f, 0.0f);
	}
}
