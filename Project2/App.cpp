#pragma once
#include "ServerSocket.h"
#include <iostream>

#pragma comment(lib,"wsock32.lib")

int main(int argc, char* argv[]) {

	ServerSocket* serverSocket = nullptr;

	try {

		int portNumber = std::stoi(argv[1]);

		std::cout << "Server is listening on port: " << portNumber << std::endl;


		serverSocket = new ServerSocket(portNumber);

		Socket* socket = serverSocket->acceptConnections();

		socket->info();
		
		InputStream* inputStream = socket->getInputStream();

		std::cout << inputStream->readFloat() << std::endl;
		std::cout << inputStream->readUTF8() << std::endl;
		std::cout << inputStream->readFloat() << std::endl;
		std::cout << inputStream->readUTF8() << std::endl;
		std::cout << inputStream->readInt() << std::endl;

	} catch (SocketException e) {
		std::cout << e.message() << std::endl;
		serverSocket->close();
	}

	system("pause");

	return 0;
}