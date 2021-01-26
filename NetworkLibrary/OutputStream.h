#pragma once
#include <winsock.h>
#include <string>

#define capacity 4080
#define increment 1080

class OutputStream
{
private:
	SOCKET socket;
	byte* bytes;
	int offset;
	int maxSize;

public:
	OutputStream(SOCKET);
	void writeByte(unsigned char);
	void writeInt(int);
	void writeFloat(float);
	void writeLong(long);
	void writeDouble(double);
	void writeUTF8(std::string);
	void flush();

private:
	int size(const char*);
	void extend();
	bool check(int);
};

