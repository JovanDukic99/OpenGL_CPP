#include "InputStream.h"
#include "SocketException.h"
#include "IOErrors.h"
#include <iostream>

using namespace std;

InputStream::InputStream(SOCKET socket) : socket(socket)
{

}

byte InputStream::readByte()
{
	int length = sizeof(byte);
	int amount = 0;

	byte* bytes = new byte[length];
	byte* begin = bytes;

	while (length > 0)
	{
		if ((amount = recv(socket, (char*)begin, length, 0)) == SOCKET_ERROR)
		{
			throw SocketException(BYTE_ERROR);
		}
		else
		{
			length = length - amount;
			begin = begin + amount;
		}
	}

	byte result = bytes[0];

	delete[] bytes;

	return result;
}

int InputStream::readInt()
{
	int length = sizeof(int);
	int amount = 0;

	byte* bytes = new byte[length];
	byte* begin = bytes;

	while (length > 0)
	{
		if ((amount = recv(socket, (char*)begin, length, 0)) == SOCKET_ERROR)
		{
			throw SocketException(INTEGER_ERROR);
		}
		else
		{
			length = length - amount;
			begin = begin + amount;
		}
	}

	int result = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);

	delete[] bytes;

	return result;
}

float InputStream::readFloat()
{
	int length = sizeof(float);
	int amount = 0;

	byte* bytes = new byte[length];
	byte* begin = bytes;

	while (length > 0)
	{
		if ((amount = recv(socket, (char*)begin, length, 0)) == SOCKET_ERROR)
		{
			throw SocketException(FLOAT_ERROR);
		}
		else
		{
			length = length - amount;
			begin = begin + amount;
		}
	}

	float result;

	memcpy(&result, bytes, sizeof(float));

	delete[] bytes;

	return result;
}

long InputStream::readLong()
{
	int length = sizeof(long);
	int amount = 0;

	byte* bytes = new byte[length];
	byte* begin = bytes;

	while (length > 0)
	{
		if ((amount = recv(socket, (char*)begin, length, 0)) == SOCKET_ERROR)
		{
			throw SocketException(LONG_ERROR);
		}
		else
		{
			length = length - amount;
			begin = begin + amount;
		}
	}

	long result;

	memcpy(&result, bytes, sizeof(long));

	delete[] bytes;

	return result;
}

double InputStream::readDouble()
{
	int length = sizeof(double);
	int amount = 0;

	byte* bytes = new byte[length];
	byte* begin = bytes;

	while (length > 0)
	{
		if ((amount = recv(socket, (char*)begin, length, 0)) == SOCKET_ERROR)
		{
			throw SocketException(DOUBLE_ERROR);
		}
		else
		{
			length = length - amount;
			begin = begin + amount;
		}
	}

	double result;

	memcpy(&result, bytes, sizeof(double));

	delete[] bytes;

	return result;
}

std::string InputStream::readUTF8()
{
	int lenght = readInt();
	int amount = 0;

	byte* bytes = new byte[lenght];
	byte* begin = bytes;

	memset(bytes, 0, lenght);

	while (lenght > 0)
	{
		if ((amount = recv(socket, (char*)begin, lenght, 0)) == SOCKET_ERROR)
		{
			throw SocketException(UTF8_ERROR);
		}
		else
		{
			lenght = lenght - amount;
			begin = begin + amount;
		}
	}

	std::string result = createString(bytes);

	delete[] bytes;

	return result;
}

std::string InputStream::createString(byte* bytes)
{
	std::string result;
	int t = 0;

	while (bytes[t] != 0)
	{
		result = result + (char)bytes[t++];
	}

	return result;
}