#include "IOManager.h"
#include <fstream>

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	// read file as binary
	std::ifstream file(filePath, std::ios::binary);

	// check for errors
	if (file.fail()) {
		return false;
	}

	// seek to the end to see how big is a file
	// put a file cursor at the end of file
	// (offset, from beginning or end)
	file.seekg(0, std::ios::end);

	// get file size
	// tellg() - tells how many bytes are before the current location
	long long fileSize = file.tellg();

	// return to beginning
	file.seekg(0, std::ios::beg);

	// reduce the file size by any header bytes that might be present
	fileSize = fileSize - file.tellg();

	// read from file
	buffer.resize((const int) fileSize);
	file.read((char*) &(buffer[0]), fileSize);

	// close stream (btw, fstream automatically closes after being destroyed)
	file.close();

	return true;
}
