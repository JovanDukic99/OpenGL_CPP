#pragma once
#include "Socket.h"
#include "SocketException.h"
#include "IOErrors.h"

#pragma comment(lib,"wsock32.lib")

Socket::Socket(SOCKET socketID, sockaddr_in* clientAddress) : socketID(socketID), clientAddress(clientAddress), serverAddress(nullptr)
{
	initInfo();
}

Socket::Socket(int portNumber, std::string hostName) : clientAddress(nullptr), serverAddress(new sockaddr_in)
{
	init(portNumber, hostName);
}

void Socket::init(int portNumber, std::string hostName) {
	initWinsock();
	initSocket();
	initServerAddress(portNumber, hostName);
	initInfo();
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
	serverAddress->sin_family = AF_INET;
	serverAddress->sin_port = htons(portNumber);
	PHOSTENT phostent = gethostbyname(hostName.c_str());

	if (phostent == nullptr) {
		throw SocketException(DNS_ERROR);
	}

	memcpy((char FAR*) & (serverAddress->sin_addr), phostent->h_addr, phostent->h_length);
}

void Socket::connectToServer() {
	if (connect(socketID, (PSOCKADDR)serverAddress, sizeof(*serverAddress)) == SOCKET_ERROR) {
		throw SocketException(SOCKET_ERROR_6);
	}
}

void Socket::close() {
	WSACleanup();
}

void Socket::initInfo()
{
	if (check()) {
		setInfo(clientAddress);
	}
	else {
		setInfo(serverAddress);
	}
}

void Socket::setInfo(sockaddr_in* socketAddress)
{
	PHOSTENT phostent = gethostbyaddr((char FAR*) & socketAddress->sin_addr, sizeof(*socketAddress), AF_INET);
	hostName = phostent->h_name;

	IP = inet_ntoa(socketAddress->sin_addr);
	portNumber = ntohs(socketAddress->sin_port);
}

std::string Socket::getIP()
{
	return IP;
}

int Socket::getPortNumber()
{
	return portNumber;
}

std::string Socket::getHostName()
{
	return hostName;
}

bool Socket::check()
{
	return serverAddress == nullptr;
}

OutputStream* Socket::getOutputStream()
{
	return new OutputStream(socketID);
}

InputStream* Socket::getInputStream()
{
	return new InputStream(socketID);
}



