#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "TCPAcceptor.h"

using namespace std;

vector<thread> threads;
vector<TCPStream*> channel;

void serve(TCPStream* stream)
{
	ssize_t len;
	char line[256];
	while ( (len = stream->receive(line, sizeof(line))) > 0 ) {
		line[len] = 0;
		cout << "received - " << line << "\n" << endl;
		for (auto iter = channel.begin(), end = channel.end(); iter != end; ++iter) {
			bool close_conn = false;
			if ( (*iter)->send(line, len) < 0) {
				if (stream == *iter) close_conn = true;
				iter = channel.erase(iter);
				if (close_conn) return;
			}
		}
	}
	channel.erase(std::remove(channel.begin(), channel.end(), stream),
	              channel.end());
}

void do_join(thread& t)
{
	t.join();
}

void join_all(vector<thread>& threads)
{
	for_each(threads.begin(), threads.end(), do_join);
}


int main(int argc, char** argv)
{
	if (argc < 2 || argc > 4) {
		cout << "Usage: server <port> [<ip>]\n" << endl;
		return EXIT_FAILURE;
	}

	// vector<vector> channels;
	TCPStream* stream = nullptr;
	TCPAcceptor* acceptor = nullptr;

	if (argc == 3) {
		acceptor = new TCPAcceptor(atoi(argv[1]), argv[2]);
	}
	else {
		acceptor = new TCPAcceptor(atoi(argv[1]));
	}


	if (acceptor->start() == 0) {
		for (;;) {
			stream = acceptor->accept();
			if (stream) {
				threads.push_back(thread(serve, stream));
				channel.push_back(stream);
				stream = nullptr;
			}
		}
	}
	return EXIT_SUCCESS;
}


// TODO: remove dead threads
// TODO: not sure if the send side close_conn is necessary
