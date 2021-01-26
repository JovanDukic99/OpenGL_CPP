#pragma once
#include "InputStream.h"
#include "SocketException.h"
#include "IOErrors.h"

InputStream::InputStream(SOCKET socket) : socket(socket)
{

}

byte InputStream::readByte()
{
	int length = sizeof(byte);
	byte* bytes = new byte[length];

	memset(bytes, 0, length);
	readData(bytes, length, BYTE_ERROR);

	byte result = bytes[0];

	delete[] bytes;
	return result;
}

int InputStream::readInt()
{
	int length = sizeof(int);
	byte* bytes = new byte[length];

	memset(bytes, 0, length);
	readData(bytes, length, INTEGER_ERROR);

	int result = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);

	delete[] bytes;
	return result;
}

float InputStream::readFloat()
{
	int length = sizeof(float);
	byte* bytes = new byte[length];

	memset(bytes, 0, length);
	readData(bytes, length, FLOAT_ERROR);

	float result;
	memcpy(&result, bytes, sizeof(float));

	delete[] bytes;
	return result;
}

long InputStream::readLong()
{
	int length = sizeof(long);
	byte* bytes = new byte[length];

	memset(bytes, 0, length);
	readData(bytes, length, LONG_ERROR);

	long result;
	memcpy(&result, bytes, sizeof(long));

	delete[] bytes;
	return result;
}

double InputStream::readDouble()
{
	int length = sizeof(double);
	byte* bytes = new byte[length];

	memset(bytes, 0, length);
	readData(bytes, length, DOUBLE_ERROR);

	double result;
	memcpy(&result, bytes, sizeof(double));

	delete[] bytes;
	return result;
}

std::string InputStream::readUTF8()
{
	int length = readInt();
	byte* bytes = new byte[length];

	memset(bytes, 0, length);
	readData(bytes, length, UTF8_ERROR);

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

void InputStream::readData(byte* bytes, int lenght, std::string error)
{
	int amount = 0;
	while (lenght > 0)
	{
		if ((amount = recv(socket, (char*)bytes, lenght, 0)) == SOCKET_ERROR)
		{
			if (connectionReset(WSAGetLastError())) {
				throw SocketException(CONNECTION_RESET);
			}
			else {
				throw SocketException(error);
			}
		}
		else
		{
			lenght = lenght - amount;
			bytes = bytes + amount;
		}
	}
}

bool InputStream::connectionReset(int error)
{
	return error == CONNECTION_RESET_CODE;
}