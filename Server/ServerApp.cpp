#include <ServerSocket.h>
#include <iostream>

int main(int args, char* argv[]) {

	try {

		std::cout << "Server is running..." << std::endl;

		ServerSocket* serverSocket = new ServerSocket(std::stoi(argv[1]));

		while (1) {
			Socket* socket = serverSocket->acceptConnections();
			
			InputStream* inputStream = socket->getInputStream();

			std::cout << "New client has been accepted!" << std::endl;
			std::cout << inputStream->readUTF8() << std::endl;
		}
	}
	catch (SocketException e) {
		std::cout << e.message() << std::endl;
	}

	system("pause");

	return 0;
}