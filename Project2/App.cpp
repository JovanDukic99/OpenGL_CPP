#pragma once
#include "ServerSocket.h"
#include "Config.h"

int main() {

	ServerSocket* serverSocket = nullptr;

	try {
		serverSocket = new ServerSocket(PORT_NUMBER);

		Socket* socket = serverSocket->acceptConnections();
		
		InputStream* inputStream = socket->getInputStream();

		std::cout << inputStream->readFloat() << std::endl;
		std::cout << inputStream->readInt() << std::endl;
	} catch (SocketException e) {
		std::cout << e.message() << std::endl;
		serverSocket->close();
	}

	system("pause");

	return 0;
}