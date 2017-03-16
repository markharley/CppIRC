#include "Server.h"


void Server::serve(User& user)
{
	ssize_t len;
	char line[256];
	string command = "";
	while ( (len = user->receive(line, sizeof(line))) > 0 ) {
		line[len] = 0;
		cout << "received - " << line << "\n" << endl;
		string newPiece(line);
		command += newPiece;

		if (newPiece.back() == '\n') {
			commandHandler.handle_command(command, *this, user);
			cout << "command - " << command << endl;
			command = "";
		}
	}
	user.close()
}

void Server::add_connection(TCPStream* stream)
{
	threads.push_back(thread(Server::serve, stream));
}

void Server::stop()
{
	// TODO
	// Close connections and stop threads
}

Channel& Server::new_channel(string name)
{
	newChannel = Channel::Channel(name);
	bool ok = channels.insert({name, newChannel});

	if (!ok){
		throw ChannelExistsError();
	}
	return newChannel;
}

Channel& Server::get_channel(string name)
{
	auto search = channels.find(name)

	if (search == channels.end()) {
		throw ChannelDoesntExistError();
	}
	return search->second;
}

void Server::do_join(thread& t)
{
	t.join();
}

void Server::join_all(vector<thread>& threads)
{
	for_each(threads.begin(), threads.end(), do_join);
}
