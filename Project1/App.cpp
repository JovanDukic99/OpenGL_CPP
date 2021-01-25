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

		outputStream->writeFloat(46.0f);
		outputStream->writeUTF8("LET IT SNOWWWWW");
		outputStream->writeFloat(40.0f);
		outputStream->writeUTF8("Work finally pls!");
		outputStream->writeInt(30);
		outputStream->flush();
	} catch (SocketException e) {
		std::cout << e.message() << std::endl;
		socket->close();
	}
	
	system("pause");

	return 0;
}