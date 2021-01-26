#include <Network/Socket.h> 

int main() {

	try {
		Socket* socket = new Socket(54000, "ec2-18-193-123-247.eu-central-1.compute.amazonaws.com");
	}
	catch (SocketException e) {
		std::cout << e.message() << std::endl;
	}

	system("pause");

	return 0;
}