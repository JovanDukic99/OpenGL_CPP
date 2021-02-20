#include "Image.h"
#include <cstring>

Image::Image(int width, int height) : width(width), height(height), buffer(nullptr) {
	init();
}

Image::Image(const Image& image) {
	setWidth(image.width);
	setHeight(image.height);
	init();
	fillBuffer(image);
}

Image::~Image() {
	for (int i = 0; i < height; i++) {
		delete[] buffer[i];
	}
	delete[] buffer;
}

// operator overload
int* Image::operator[](int index) {
	return buffer[index];
}


// getters
int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

// private functions : init / setters
void Image::init() {
	buffer = new int* [height];
	for (int i = 0; i < height; i++) {
		buffer[i] = new int[width];
	}
}

// setters
void Image::setWidth(int width) {
	this->width = width;
}

void Image::setHeight(int height) {
	this->height = height;
}

void Image::fillBuffer(const Image& image) {
	for (int i = 0; i < height; i++) {
		std::memcpy(buffer[i], image.buffer[i], width * sizeof(int));
	}
}