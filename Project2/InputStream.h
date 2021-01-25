#pragma once
#include <winsock.h>
#include <string>
class InputStream
{
private:
	SOCKET socket;

public:
	InputStream(SOCKET);

	byte readByte();
	int readInt();
	float readFloat();
	long readLong();
	double readDouble();
	std::string readUTF8();

private:
	std::string createString(byte*);
};

