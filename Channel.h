#pragma once

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "TCPSockets/TCPStream.h"

using namespace std;

class Channel
{
public:
	friend class Server;
	~Channel();

	void remove_channel_member(TCPStream* stream);
	void change_name(string newName);

protected:
	vector<User*> members;
	string name;

private:
	Channel() : name("") {};
	Channel(string _name) : name(_name) {};
};
