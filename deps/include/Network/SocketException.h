#pragma once
#include <string>
class SocketException
{
public:
	std::string error;

	SocketException(std::string error);
	std::string message();
};

