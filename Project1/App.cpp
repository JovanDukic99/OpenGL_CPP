#include "Socket.h"
#include "Config.h"
#include "Client.h"
#include <thread>
#include <iostream>

int main() {

	Socket* socket = nullptr;

	try {
		socket = new Socket(PORT_NUMBER, "localhost");

		OutputStream* outputStream = socket->getOutputStream();

		outputStream->writeFloat(10.0f);
		outputStream->writeInt(20);
		outputStream->flush();
	} catch (SocketException e) {
		std::cout << e.message() << std::endl;
		socket->close();
	}
	
	system("pause");

	return 0;
}