#include <Socket.h> 
#include <iostream>

int main(int args, char* argv[]) {

	try {
		Socket* socket = new Socket(std::stoi(argv[1]), "localhost");

		OutputStream* outputStream = socket->getOutputStream();

		outputStream->writeUTF8("Hello World!");
		outputStream->flush();
	}
	catch (SocketException e) {
		std::cout << e.message() << std::endl;
	}

	system("pause");

	return 0;
}