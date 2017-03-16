#include "Channel.h"

void Channel::remove_channel_member(TCPStream* stream)
{
	members.erase(std::remove(members.begin(), members.end(), stream),
	              members.end());
}

void Channel::change_name(string newName) : name(newName)
{
    if (name_validate(newName)) {
        name = newName;
    }
    else {
        throw UhOhError(); // Need to make an actual exception here
    }
}
