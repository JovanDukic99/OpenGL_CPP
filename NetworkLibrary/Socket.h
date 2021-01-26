#pragma once
#ifndef SOCK
#define SOCK

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

#include <Windows.h>
#include <iostream>
#include <winsock.h>
#include <string>
#include "InputStream.h"
#include "OutputStream.h"
#include "SocketException.h"

	class Socket
	{
	private:
		SOCKET socketID;
		sockaddr_in* serverAddress, * clientAddress;
		std::string IP;
		std::string hostName;
		int portNumber;

	public:
		Socket(SOCKET socketID, sockaddr_in* clientAddress);
		Socket(int portNumber, std::string hostName);

		OutputStream* getOutputStream();
		InputStream* getInputStream();

		std::string getIP();
		std::string getHostName();

		int getPortNumber();

		void info();
		void close();

	private:
		void init(int portNumber, std::string hostName);
		void initInfo();
		void setInfo(sockaddr_in* socketAddress);
		void initWinsock();
		void initSocket();
		void initServerAddress(int portNumber, std::string hostName);
		void connectToServer();
		bool check();
	};

#ifdef _cplusplus
}
#endif // _cplusplus

#endif // !SOCKET