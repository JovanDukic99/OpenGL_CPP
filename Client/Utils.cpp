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
