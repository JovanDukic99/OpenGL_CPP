enum class ConnectionState {
	DISCONNECT = 0,
	CONNECT = 10
};

extern const ConnectionState getState(char *buff) {
	unsigned char type = (unsigned char) (*buff);
	if (type == 0) {
		return ConnectionState::DISCONNECT;
	}
	else if (type == 10) {
		return ConnectionState::CONNECT;
	}
	else {
		return ConnectionState::DISCONNECT;
	}
}