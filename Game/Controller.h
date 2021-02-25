#pragma once
#include <SearchSpace.h>
#include <Edge.h>
#include <vector>
class Controller
{
private:
	static Controller* controller;
	SearchSpace searchSpace;
	std::vector<Edge*> edges;
private:
	Controller();
public:
	static Controller* getInstance();
	SearchSpace& getSearchSpace();
	std::vector<Edge*>& getEdges();
};

