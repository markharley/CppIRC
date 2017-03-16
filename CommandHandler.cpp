#include "CommandHandler.h"

void CommandHandler::run_command(string commName, Server& server, Channel& channel, User& user)
{
	command = commands[commName];
	(*command)(server, channel, user);
}

void CommandHandler::parse_command(string commandName)
{

}

vector<string> split_string(string toSplit, string splitChar)
{
	vector<string> result;

    	char_separator<char> sep(" ");
    	tokenizer<char_separator<char>> tokens(toSplit, sep);
    	for (const auto& t : tokens) {
        	cout << t << "." << endl;
    	}
}
