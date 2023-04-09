#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <sys/epoll.h>
#include <vector>

#include "socket.hpp"

class Server : public Socket{
	public:
		Server();
		Server(const std::string& configFilePath);
		~Server();

		void setPort(int port);
		int getPort() const;

		void run();

	private:
		static const int BUFFER_SIZE = 1024;
		static const int MAX_EVENTS = 5;

		void handle_client(int clientSocket);
		void send_response(int clientSocket, const std::string response);

		int _serverSocket;
		const std::string _configFilePath;
		int _port;
};

#endif // Server_HPP
