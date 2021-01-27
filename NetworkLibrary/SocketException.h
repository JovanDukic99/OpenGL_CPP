#pragma once
#ifndef SOCKET_EXCEPTION
#define SOCKET_EXCEPTION

#include <string>

	class SocketException
	{
	public:
		std::string error;

		SocketException(std::string error);
		std::string message();
	};

#endif // !SOCKET_EXCEPTION