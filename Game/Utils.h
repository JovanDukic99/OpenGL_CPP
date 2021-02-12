#pragma once
#include <string>
#include <vector>
#include "Block.h"
#include "EntityBase.h"
class Utils
{
public:
	static void loadMap(std::string filePath, std::vector<Block>& blocks);
	static bool squareCollision(EntityBase e1, EntityBase e2);
};

