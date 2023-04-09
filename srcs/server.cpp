#include "server.hpp"

Server::Server()
{
}

Server::Server(const std::string &configFilePath) : _configFilePath(configFilePath)
{
	std::ifstream configFile(_configFilePath.c_str());
	if (!configFile || !configFile.is_open())
	{
		std::cerr << "Error: config file error: " << _configFilePath << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (std::getline(configFile, line))
	{
		std::istringstream iss(line);
		std::string key, value;
		if (!(iss >> key >> value))
		{
			std::cerr << "Error: Invalid config line:" << line << std::endl;
			exit(EXIT_FAILURE);
		}
		if (key == "PORT")
		{
			setPort(atoi(value.c_str()));
		}
	}
}

Server::~Server()
{
	close(_serverSocket);
}

void Server::run()
{
	_serverSocket = create_server_socket();
	set_socket_options(_serverSocket);
	bind_server_socket(_serverSocket, getPort());
	listen_on_server_socket(_serverSocket);
	std::cout << "Server Listening on port " << getPort() << std::endl;

	int epoll_fd = epoll_create(0);
	if (epoll_fd == -1)
	{
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = _serverSocket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _serverSocket, &event) == -1) {
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}

	std::vector<struct epoll_event> events(MAX_EVENTS);
	char buffer[BUFFER_SIZE];

	while (true) {
		int event_count = epoll_wait(epoll_fd, events.data(), events.size(), -1);
		std::cout << "event_count: " << event_count << std::endl;
		if (event_count < 0) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < event_count; i++) {
			if (events[i].data.fd == _serverSocket) {
				int clientSocket = accept_client(_serverSocket);
				event.events = EPOLLIN | EPOLLOUT;
				event.data.fd = clientSocket;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientSocket, &event) == -1) {
					perror("epoll_ctl");
					exit(EXIT_FAILURE);
				}
			}
			else {
				int nread = recv(events[i].data.fd, buffer, BUFFER_SIZE, 0);
				if (nread < 1) {
					if (errno != EAGAIN || errno == EWOULDBLOCK) {
						break;
					}
					else {
						perror("recv");
						close(events[i].data.fd);
					}
				}
				else {
					int nwritten = send(events[i].data.fd, buffer, nread, 0);
					if (nwritten < 0) {
						if (errno != EAGAIN || errno == EWOULDBLOCK) {
							break;
							perror("send");
							close(events[i].data.fd);
						}
					}
				}
			}
		}
	}
}

void Server::send_response(int clientSocket, const std::string response)
{
	int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
	if (bytesSent < 0)
	{
		std::cerr << "Error writing to client socket: " << strerror(errno) << std::endl;
	}
}

void Server::setPort(int port)
{
	_port = port;
}

int Server::getPort() const
{
	return _port;
}
