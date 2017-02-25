#pragma once

#include <string>
#include <netinet/in.h>
#include "TCPStream.h"

using namespace std;

class TCPAcceptor
{
protected:
	int m_lsd;
	int m_port;
	string m_address;
	bool m_listening;

public:
	TCPAcceptor(int port, const char* address="");
	~TCPAcceptor();

	int start();
	TCPStream* accept();

private:
	TCPAcceptor() {}
};
