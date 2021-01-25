#pragma once
#include <string>

static const std::string SOCKET_ERROR_1 = "Failed to initialize WSADATA.";
static const std::string SOCKET_ERROR_2 = "Socket creation has failed.";
static const std::string SOCKET_ERROR_3 = "Connecting to server has failed.";

static const std::string OUTPUT_STREAM_ERROR = "OutputStream error: Failed to send data.";
static const std::string BYTE_ERROR= "InputStream error: Failed to read BYTE data type.";
static const std::string INTEGER_ERROR = "InputStream error: Failed to read INTEGER data type.";
static const std::string FLOAT_ERROR = "InputStream error: Failed to read FLOAT data type.";
static const std::string LONG_ERROR = "InputStream error: Failed to read LONG data type.";
static const std::string DOUBLE_ERROR = "InputStream error: Failed to read DOUBLE data type.";
static const std::string UTF8_ERROR = "InputStream error: Failed to read UTF8 (string) data type.";
