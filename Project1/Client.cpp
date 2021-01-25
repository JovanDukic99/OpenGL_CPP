#include "Client.h"
#include "ConnectionState.h"
#include "Utils.h"
#include <iostream>

Client::Client(Socket *socket) : socket(socket)
{

}

void Client::operator()()
{
	run();
}

void Client::run()
{
	
}

