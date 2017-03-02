#include <arpa/inet.h>
#include "TCPStream.h"

TCPStream::TCPStream(int _sd, struct sockaddr_in* address)
	: sd(_sd)
{
	char ip[50];
	inet_ntop(PF_INET,
			  (struct in_addr*)&(address->sin_addr.s_addr),
			  ip,
			  sizeof(ip)-1
			 );

	peerIP = ip;
	peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream()
{
	close(sd);
}

ssize_t TCPStream::send(const char* buffer, size_t len)
{
	return write(sd, buffer, len);
}

ssize_t TCPStream::send(const string& buffer, size_t len)
{
	return write(sd, buffer.c_str(), len);
}

ssize_t TCPStream::receive(char* buffer, size_t len, int timeout)
{
	if (timeout <= 0) return read(sd, buffer, len);

	if(waitForReadEvent(timeout) == true)
	{
		return read(sd, buffer, len);
	}
	return connectionTimedOut;
}

string TCPStream::getPeerIP()
{
	return peerIP;
}

int TCPStream::getPeerPort()
{
	return peerPort;
}

bool TCPStream::waitForReadEvent(int timeout)
{
	fd_set sdset;
	struct timeval tv;

	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	FD_ZERO(&sdset);
	FD_SET(sd, &sdset);
	if (select(sd+1, &sdset, NULL, NULL, &tv) > 0)
	{
		return true;
	}
	return false;
}
