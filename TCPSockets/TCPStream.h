#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std;

class TCPStream
{
public:
	friend class TCPAcceptor;
	friend class TCPConnector;

	~TCPStream();

	ssize_t send(const char* buffer, size_t len);
	ssize_t send(const string& buffer, size_t len);
	ssize_t receive(char* buffer, size_t len, int timeout=0);
	// ssize_t receive(string* buffer, int timeout=0);

	string getPeerIP();
	int getPeerPort();

	enum {
		connectionClosed = 0,
		connectionReset = -1,
		connectionTimedOut = -2
	};


protected:
	int sd;
	string peerIP;
	int peerPort;


private:
	bool waitForReadEvent(int timeout);

	TCPStream(int sd, struct sockaddr_in* address);
	TCPStream();
	TCPStream(const TCPStream& stream);
};
