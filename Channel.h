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

    // RFC2812 - Max length 50, starting with '&', '#', '+', or '!'
    //         - Cannot contain spaces, a control G (^G or ASCII 7)
    //           or a comma.
    //         - Case insensitive
	string name;

private:
	Channel() : name("") {};
	Channel(string _name) : name(_name) {};

    bool name_validate(string newName);
};
