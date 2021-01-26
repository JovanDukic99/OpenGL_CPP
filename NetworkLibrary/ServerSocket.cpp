#include "ServerSocket.h"
#include "SocketException.h"
#include "IOErrors.h"
#include <iostream>

ServerSocket::ServerSocket(int portNumber)
{
	init(portNumber);
}

void ServerSocket::init(int portNumber) {
	initWinsock();
	initSocket();
	initServerAddress(portNumber);
	bindServerAddress();
	initListening();
}

void ServerSocket::initWinsock() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw SocketException(SOCKET_ERROR_1);
	}
}

void ServerSocket::initSocket() {
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		throw SocketException(SOCKET_ERROR_2);
	}
}

void ServerSocket::initServerAddress(int portNumber) {
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void ServerSocket::bindServerAddress() {
	if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		throw SocketException(SOCKET_ERROR_3);
	}
}

void ServerSocket::initListening() {
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		throw SocketException(SOCKET_ERROR_4);
	}
}

Socket* ServerSocket::acceptConnections() {
	sockaddr_in clientAddress;
	int clientAddressSize = sizeof(clientAddress);

	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientAddressSize);
	if (clientSocket == INVALID_SOCKET) {
		throw SocketException(SOCKET_ERROR_5);
	}

	return new Socket(clientSocket, &clientAddress);
}

void ServerSocket::close()
{
	WSACleanup();
}
