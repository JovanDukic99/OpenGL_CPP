#pragma once
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
	SOCKET socketID;;
	sockaddr_in serverAddress;

public:
	Socket(SOCKET socketID);
	Socket(int portNumber, std::string hostName);
	OutputStream* getOutputStream();
	InputStream* getInputStream();
	void close();

private:
	void init(int portNumber, std::string hostName);
	void initWinsock();
	void initSocket();
	void initServerAddress(int portNumber, std::string hostName);
	void connectToServer();
};

