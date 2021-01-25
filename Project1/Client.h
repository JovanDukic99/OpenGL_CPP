#include "Socket.h"

class Client {
private:
	Socket *socket;

public:
	Client(Socket *socket);
	void operator()();

private:
	void run();
};
