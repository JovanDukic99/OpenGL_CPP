#pragma once
#include <string>
#include "SDLError.h"

class SDLException
{
private:
	std::string error;

public:
	SDLException(std::string error);
	std::string message();
};

