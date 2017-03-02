#pragma once

#include <string>

class User
{
public:
	friend class Server;

	~User();

	ssize_t receive(char* buffer, size_t len, int timeout=0);
	ssize_t send(const char* buffer, size_t len);
	ssize_t send(const string& buffer, size_t len);

	void close();

private:
	User();

	vector<Channel*> channels;
	string nick;
	TCPStream& stream;


};
