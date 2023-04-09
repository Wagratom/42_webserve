#include "server.hpp"

Socket::Socket() {}

Socket::~Socket() {}

int Socket::create_server_socket() {
	int serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cerr << "Error creating server socket\n";
		exit(EXIT_FAILURE);
	}
	return serverSocket;
}

void Socket::set_socket_options(int& serverSocket) {
	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "Error setting server socket options\n";
		exit(EXIT_FAILURE);
	}
}

void Socket::bind_server_socket(int& serverSocket, int port) {
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cerr << "Error binding server socket\n";
		exit(EXIT_FAILURE);
	}
}

void Socket::listen_on_server_socket(int& serverSocket) {
	if (listen(serverSocket, BACKLOG) < 0) {
		std::cerr << "Error listening on server socket\n";
		exit(EXIT_FAILURE);
	}
}

int Socket::accept_client(int& serverSocket) {
	struct sockaddr_in clientAddress;
	int addrlen = sizeof(clientAddress);
	int clientSocket;
	if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, (socklen_t*)&addrlen)) < 0) {
		std::cerr << "Error accepting client connection\n";
		exit(EXIT_FAILURE);
	}

	// Set the O_NONBLOCK flag on the client socket
	int flags = fcntl(clientSocket, F_GETFL, 0);
	if ((flags == -1) || (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1)) {
		std::cerr << "Error setting client socket to non-blocking\n";
		exit(EXIT_FAILURE);
	}

	return clientSocket;
}

void Socket::close_socket(int& socket) {
	close(socket);
}
