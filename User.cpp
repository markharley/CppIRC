#include "User.h"

ssize_t User::receive(char* buffer, size_t len, int timeout=0)
{
	return stream->receive(char* buffer, size_t len, int timeout=0);
}

ssize_t User::send(const char* buffer, size_t len)
{
	return stream->send(const char* buffer, size_t len);
}

ssize_t User::send(const string& buffer, size_t len)
{
	return stream->send(const string& buffer, size_t len);
}

void User::close()
{
	//remove from channels
	//close stream
	//remove thread from server vector(?)
}
