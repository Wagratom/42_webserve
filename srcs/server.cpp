#include "server.hpp"

Server::Server() {
}

Server::Server(const std::string& configFilePath) : _configFilePath(configFilePath) {
	std::ifstream configFile(_configFilePath.c_str());
	if (!configFile || !configFile.is_open()) {
		std::cerr << "Error: config file error: " << _configFilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (std::getline(configFile, line)) {
		std::istringstream iss(line);
		std::string key, value;
		if (!(iss >> key >> value)) {
			std::cerr << "Error: Invalid config line:" << line << std::endl;
			exit(EXIT_FAILURE);
		}
		if (key == "PORT") {
			setPort(atoi(value.c_str()));
		}
	}
}

Server::~Server() {
	close(_serverSocket);
}

void Server::run() {
	_serverSocket = create_server_socket();
	set_socket_options(_serverSocket);
	bind_server_socket(_serverSocket, getPort());
	listen_on_server_socket(_serverSocket);
	std::cout << "Server Listening on port " << getPort() << std::endl;

	while (true) {
		int clientSocket = accept_client(_serverSocket);
		std::cout << "Accepted client connection" << std::endl;

		pid_t pid = fork();
		if (pid < 0) {
			std::cerr << "Error forking: " << strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) {
			close(_serverSocket);

			std::string response = "HTTP/1.1 200 OK\r\n"
				"Content-Type: text/html\r\n"
				"\r\n"
				"<html><body><h1>Bem Vindo a World Wide Web!</h1></body></html>";
			send_response(clientSocket, response);

			handle_client(clientSocket);
			close(clientSocket);
			exit(EXIT_SUCCESS);
		}
		else {
			close(clientSocket);
		}
	}
}

void Server::handle_client(int clientSocket) {
	char buffer[BUFFER_SIZE];
	int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
	if (bytesRead < 0) {
		std::cerr << "Error reading from client socket: " << strerror(errno) << std::endl;
		return ;
	}

	std::string request(buffer, bytesRead);
	std::string response = "HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"\r\n"
	"<html><body><h1>Solicitação Ouvida, resposta ...!</h1></body></html>";

	send_response(clientSocket, response);
	std::cout << "Sent response to client" << std::endl;
}

void Server::send_response(int clientSocket, const std::string response) {
	int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
	if (bytesSent < 0) {
		std::cerr << "Error writing to client socket: " << strerror(errno) << std::endl;
	}
}

void Server::setPort(int port) {
	_port = port;
}

int Server::getPort() const {
	return _port;
}
