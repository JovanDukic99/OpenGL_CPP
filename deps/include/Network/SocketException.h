#pragma once
#ifndef SOCKET_EXCEPTION
#define SOCKET_EXCEPTION

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

#include <string>

	class SocketException
	{
	public:
		std::string error;

		SocketException(std::string error);
		std::string message();
	};

#ifdef _cplusplus
}
#endif // _cplusplus

#endif // !SOCKET_EXCEPTION