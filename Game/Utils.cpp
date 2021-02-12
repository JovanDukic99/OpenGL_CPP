#include "Utils.h"
#include "Config.h"
#include <ImageLoader.h>

void Utils::loadMap(std::string filePath, std::vector<Block>& blocks) {
	Image image = ImageLoader::loadImage(filePath);

	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			int pixel = image[i][j];

			int r = (pixel >> 24) & 0xff;
			int g = (pixel >> 16) & 0xff;
			int b = (pixel >> 8) & 0xff;
			int a = pixel & 0xff;

			if (r == 0 && g == 0 && b == 0 && a == 255) {
				float y = 2 * SCREEN_HEIGHT - i * UNIT_HEIGHT - UNIT_HEIGHT;
				float x = j * UNIT_WIDTH;
				blocks.emplace_back(x, y, UNIT_WIDTH, UNIT_HEIGHT);
			}
		}
	}

	image.clear();
}

bool Utils::squareCollision(EntityBase e1, EntityBase e2) {
	if (e1.getX() + e1.getWidth() < e2.getX()) {
		return false;
	}

	if (e2.getX() + e2.getWidth() < e1.getX()) {
		return false;
	}

	if (e1.getY() < e2.getY()) {
		return false;
	}

	if (e2.getY() + e2.getHeight() < e1.getY()) {
		return false;
	}

	return true;
}
