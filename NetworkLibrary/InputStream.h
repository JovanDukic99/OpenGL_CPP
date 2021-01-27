#pragma once
#ifndef INPUT_STREAM
#define INPUT_STREAM

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
		void readData(byte*, int, std::string);
		bool connectionReset(int);
	};


#endif // !INPUT_STREAM