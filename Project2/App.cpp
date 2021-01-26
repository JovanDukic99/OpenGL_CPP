#pragma once
#include "ServerSocket.h"
#include <iostream>

int main(int argc, char* argv[]) {

	ServerSocket* serverSocket = nullptr;

	try {

		std::cout << "Server is listening..." << std::endl;

		serverSocket = new ServerSocket(std::stoi(argv[1]));

		Socket* socket = serverSocket->acceptConnections();
		
		InputStream* inputStream = socket->getInputStream();

		std::cout << inputStream->readFloat() << std::endl;
		std::cout << inputStream->readUTF8() << std::endl;
		std::cout << inputStream->readFloat() << std::endl;
		std::cout << inputStream->readUTF8() << std::endl;
		std::cout << inputStream->readInt() << std::endl;

		socket->info();
	} catch (SocketException e) {
		std::cout << e.message() << std::endl;
		serverSocket->close();
	}

	system("pause");

	return 0;
}