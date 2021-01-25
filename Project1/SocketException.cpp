#include "SocketException.h"

SocketException::SocketException(std::string error) : error(error)
{
	
}

std::string SocketException::message()
{
	return error;
}