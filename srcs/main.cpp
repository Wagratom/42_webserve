#include "server.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: ./server <config_file>" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string configFilePath = argv[1];
	Server server(configFilePath);
	server.run();
	return 0;
}
