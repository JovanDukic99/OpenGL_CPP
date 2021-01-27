#pragma once
#ifndef IO_ERRORS
#define IO_ERRORS

#include <string>

	static const int CONNECTION_RESET_CODE = 10054;
	static const std::string CONNECTION_RESET = "Socket error: Connection reset.";

	static const std::string SOCKET_ERROR_1 = "Failed to initialize WSADATA!";
	static const std::string SOCKET_ERROR_2 = "Socket creation has failed!";
	static const std::string SOCKET_ERROR_3 = "Socket binding has failed!";
	static const std::string SOCKET_ERROR_4 = "Listening initialization has failed!";
	static const std::string SOCKET_ERROR_5 = "Failed to accept new client!";
	static const std::string SOCKET_ERROR_6 = "Failed to connect to the server!";

	static const std::string OUTPUT_STREAM_ERROR = "OutputStream error: Failed to send data.";
	static const std::string DNS_ERROR = "DNS Error: Can't translate host name to IP adress.";
	static const std::string BYTE_ERROR = "InputStream error: Failed to read BYTE data type.";
	static const std::string INTEGER_ERROR = "InputStream error: Failed to read INTEGER data type.";
	static const std::string FLOAT_ERROR = "InputStream error: Failed to read FLOAT data type.";
	static const std::string LONG_ERROR = "InputStream error: Failed to read LONG data type.";
	static const std::string DOUBLE_ERROR = "InputStream error: Failed to read DOUBLE data type.";
	static const std::string UTF8_ERROR = "InputStream error: Failed to read UTF8 (string) data type.";


#endif // !IO_ERRORS