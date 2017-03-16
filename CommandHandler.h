#pragma once

#include <string>
#include <ctdlib>
#include <vector>
#include <boost/tokenizer.hpp>
#include "User.h"

using namespace std;

typedef void (*CommandFunction_ptr)(Server& server, Channel& channel, User& user);

class CommandMap
{
public:
	CommandFunction_ptr get_command(string commName);

private:
	CommandFunction_ptr commands[];
	enum CommIndex{
		...
	}
}


class CommandHandler
{
public:
	friend class Server;

	~CommandHandler();
	void handle_command(string commName, Server& server, User& user);

protected:
	void parse_command(string commandName);
	void run_command(string commName, Server& server, User& user);

private:
	CommandHandler();
	unordered_map<string, CommandFunction_ptr> commands;

	vector<string> split_string(string ToSplit, string SplitChar);
};
