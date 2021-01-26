#include <Network/ServerSocket.h>

int main(int args, char* argv[]) {

	try {

		std::cout << "Server is running..." << std::endl;

		ServerSocket* serverSocket = new ServerSocket(std::stoi(argv[1]));

		while (1) {
			Socket* socket = serverSocket->acceptConnections();
			
			std::cout << "New client has been accepted!" << std::endl;

			socket->info();
		}
	}
	catch (SocketException e) {
		std::cout << e.message() << std::endl;
	}

	system("pause");

	return 0;
}