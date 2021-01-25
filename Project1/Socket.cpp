#include "Socket.h"
#include "SocketException.h"
#include "IOErrors.h"

Socket::Socket(SOCKET socketID) : socketID(socketID)
{
	ZeroMemory(&serverAddress, sizeof(serverAddress));
}

Socket::Socket(int portNumber, std::string hostName)
{
	init(portNumber, hostName);
}

void Socket::init(int portNumber, std::string hostName) {
	initWinsock();
	initSocket();
	initServerAddress(portNumber, hostName);
	connectToServer();
}

void Socket::initWinsock() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw SocketException(SOCKET_ERROR_1);
	}
}

void Socket::initSocket() {
	if ((socketID = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		throw SocketException(SOCKET_ERROR_2);
	}
}

void Socket::initServerAddress(int portNumber, std::string hostName) {
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
	PHOSTENT phostent = gethostbyname(hostName.c_str());
	memcpy((char FAR*) & (serverAddress.sin_addr), phostent->h_addr, phostent->h_length);
}

void Socket::connectToServer() {
	if (connect(socketID, (PSOCKADDR) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		throw SocketException(SOCKET_ERROR_3);
	}
}

void Socket::close() {
	WSACleanup();
}

OutputStream* Socket::getOutputStream()
{
	return new OutputStream(socketID);
}

InputStream* Socket::getInputStream()
{
	return new InputStream(socketID);
}



