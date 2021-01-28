#include "SDLException.h"

SDLException::SDLException(std::string error) : error(error)
{

}

std::string SDLException::message()
{
	return error;
}