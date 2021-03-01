#define _USE_MATH_DEFINES
#include "Utils.h"
#include "ImageLoader.h"
#include <iostream>
#include <cmath>

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

void Utils::loadMASP(std::string filePath, std::vector<Node*>& blocks, std::vector<Node*>& blockEdges, SearchSpace& searchSpace, float unitWidth, float unitHeight) {
	Image image = ImageLoader::loadImage(filePath);

	float mapHeight = image.getHeight() * unitHeight;
	glm::vec2 dimensions(unitWidth, unitHeight);

	searchSpace.init(image.getHeight(), image.getWidth());

	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			int pixel = image[i][j];

			int r = (pixel >> 24) & 0xff;
			int g = (pixel >> 16) & 0xff;
			int b = (pixel >> 8) & 0xff;
			int a = pixel & 0xff;

			float y = mapHeight - unitHeight * (i + 1);
			float x = j * unitWidth;

			glm::vec2 matrixPosition(j, i);
			glm::vec2 worldPosition(x, y);

			if (r == 0 && g == 0 && b == 0 && a == 255) {
				searchSpace[i][j] = Node(matrixPosition, worldPosition, dimensions, BlockType::EDGE);
				blockEdges.emplace_back(&searchSpace[i][j]);
			}
			else if(r == 0 && g == 255 && b == 0 && a == 255) {
				searchSpace[i][j] = Node(matrixPosition, worldPosition, dimensions, BlockType::BLOCK);
				blocks.emplace_back(&searchSpace[i][j]);
			}
			else {
				searchSpace[i][j] = Node(matrixPosition, worldPosition, dimensions, BlockType::NONE);
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

void Utils::createEdges(SearchSpace& searchSpace, std::vector<Node*>& blockEdges, std::vector<Edge*>& edges, float mapHeight, float unitWidth, float unitHeight) {
	// if default mode is being used for edge generation
	for (size_t i = 0; i < blockEdges.size(); i++) {
		Node* block = blockEdges[i];

		float x = block->getX();
		float y = block->getY();

		int row = block->getRowIndex();
		int column = block->getColumnIndex();

		float width = block->getWidth();
		float height = block->getHeight();

		// ================================== NORTH EDGE ===================================== 
		// if there is node on top side than skip this edge
		if ((row - 1 >= 0) && !(searchSpace.isEdge(row - 1, column) || searchSpace.isVisible(row - 1, column))) {
			// node from left, if it exists lenghten the edge, otherwise create one
			if (column - 1 >= 0 && searchSpace.isEdge(row, column - 1) && searchSpace.isVisible(row, column - 1)) {
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
		if ((row + 1 < searchSpace.getRowNumber()) && !(searchSpace.isEdge(row + 1, column) || searchSpace.isVisible(row + 1, column))) {
			// node from left
			if (column - 1 >= 0 && searchSpace.isEdge(row, column - 1) && searchSpace.isVisible(row, column - 1)) {
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
		if ((column - 1 >= 0) && !(searchSpace.isEdge(row, column - 1) || searchSpace.isVisible(row, column - 1))) {
			// node from top
			if (row - 1 >= 0 && searchSpace.isEdge(row - 1, column) && searchSpace.isVisible(row - 1, column)) {
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
		if ((column + 1 < searchSpace.getColumnNumber()) && !(searchSpace.isEdge(row, column + 1) || searchSpace.isVisible(row, column + 1))) {
			// node from top
			if (row - 1 >= 0 && searchSpace.isEdge(row - 1, column) && searchSpace.isVisible(row - 1, column)) {
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

void Utils::createLightEdges(Light& light, std::vector<Edge*>& edges) {
	float x = light.getX();
	float y = light.getY();
	float width = light.getWidth();
	float height = light.getHeight();

	Edge* west = new Edge(x, y, x, y + height, EdgeSide::WEST);
	Edge* east = new Edge(x + width, y, x + width, y + height, EdgeSide::EAST);
	Edge* north = new Edge(x, y + height, x + width, y + height, EdgeSide::NORTH);
	Edge* south = new Edge(x, y, x + width, y, EdgeSide::SOUTH);

	edges.push_back(west);
	edges.push_back(east);
	edges.push_back(north);
	edges.push_back(south);
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

void Utils::rayTracing(std::vector<Edge*>& edges, std::vector<glm::vec2>& edgePoints, std::vector<LightPoint>& intersectionPoints, glm::vec2 p) {
	for (size_t i = 0; i < edgePoints.size(); i++) {
		glm::vec2 point = edgePoints[i];

		// create additional 2 rays, one on each side
		std::vector<LightPoint> lightPoints = createRays(point, p);

		for (size_t i = 0; i < lightPoints.size(); i++) {

			LightPoint lightPoint = lightPoints[i];

			Line line1(lightPoint.getPosition(), p);

			float minDistance = INFINITY;
			glm::vec2 closestPoint(INFINITY, INFINITY);

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

			intersectionPoints.emplace_back(closestPoint, lightPoint.getAngle());

		}

	}

	std::sort(intersectionPoints.begin(), intersectionPoints.end(), sortCriteria);
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

std::vector<LightPoint> Utils::createRays(const glm::vec2& edge, const glm::vec2& source) {	
	std::vector<LightPoint> lightPoints;

	glm::vec2 vector = edge - source;

	float baseAngle = std::atan2(vector.y, vector.x);

	// the order must be the following
	for (size_t i = 0; i < 3; i++) {
		float angle = 0.0f;
		if (i == 0) {
			angle = baseAngle - 0.0001f;
		}
		else if (i == 1) {
			angle = baseAngle;
		}
		else {
			angle = baseAngle + 0.0001f;
		}
		float x = edge.x +  5000.0f * std::cos(angle);
		float y = edge.y + 5000.0f * std::sin(angle);
		lightPoints.emplace_back(glm::vec2(x, y), angle);
	}

	return lightPoints;
}

bool Utils::sortCriteria(LightPoint p1, LightPoint p2) {
	return p1.getAngle() < p2.getAngle();
}
