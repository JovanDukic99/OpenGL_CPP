#pragma once
#include <string>
#include <vector>
#include <Square.h>
class Utils
{
public:
	static void loadMap(std::string filePath, std::vector<Square>& blocks, float unitWidth, float unitHeight);
};

