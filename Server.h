#pragma once

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <exception>
#include "Channel.h"

using namespace std;

struct ChannelExistsError : public runtime_error {
   const char * what () const throw () {
      return "This channel already exists!";
   }
};

struct ChannelDoesntExistError : public runtime_error {
   const char * what () const throw () {
      return "This channel doesn't exist!";
   }
};

class Server
{
public:
	Server();
	~Server();

	void add_connection(TCPStream* stream);
	void serve(TCPStream* stream);
	void stop();

	Channel& new_channel(string channelName);
	Channel& get_channel(string channelName);

protected:
	vector<thread> threads;
	unordered_map<string, Channel> channels;

private:
	void do_join(thread& t);
	void join_all(vector<thread>& threads);
};
