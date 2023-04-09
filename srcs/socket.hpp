#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <fcntl.h>

class Socket {
	public:
		Socket();
		~Socket();

		int create_server_socket();
		void set_socket_options(int& serverSocket);
		void bind_server_socket(int& serverSocket, int port);
		void listen_on_server_socket(int& serverSocket);
		int accept_client(int& serverSocket);
		void close_socket(int& socket);

	private:
		static const int BACKLOG = 5;
};

#endif // Socket_HPP
