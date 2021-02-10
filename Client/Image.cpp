#include "Image.h"

Image::Image(int width, int height) : width(width), height(height), buffer(nullptr) {
	init();
}

void Image::init() {
	buffer = new int* [height];
	for (int i = 0; i < height; i++) {
		buffer[i] = new int[width];
	}
}

int* Image::operator[](int index) {
	return buffer[index];
}

void Image::clear() {
	for (int i = 0; i < height; i++) {
		delete[] buffer[i];
	}
	delete[] buffer;
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}