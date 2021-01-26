#pragma once
#ifndef SERVER_SOCKET
#define SERVERS_SOCKET

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <string>
#include "SocketException.h"
#include "Socket.h"
#include "InputStream.h"
#include "OutputStream.h"

	class ServerSocket
	{
	private:
		SOCKET serverSocket;
		sockaddr_in serverAddress;

	public:
		ServerSocket(int portNumber);
		Socket* acceptConnections();
		void close();

	private:
		void init(int portNumber);
		void initWinsock();
		void initSocket();
		void initServerAddress(int portNumber);
		void initListening();
		void bindServerAddress();
	};

#ifdef _cplusplus
}
#endif // _cplusplus

#endif // !SERVER_SOCKET