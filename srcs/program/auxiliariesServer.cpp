/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliariesServer.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/03 10:32:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

std::string	Server::getErrorPageMap(std::string error)
{
	if (error.empty())
		return ("");
	try {
		std::string full_path = _response->root + *_response->errorPage.at(error);
		return (*_response->errorPage.at(error));
	} catch (const std::exception& e) {
		return (_defaultErrorPage[error]);
	}
}

std::string	get_stringError(int error)
{
	if (error == 104) // Bad Request
		return ("404");
	if (error == 103) // Forbidden
		return ("403");
	return ("500");
}

bool	Server::configureEnvsServer(epoll_event& event)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen = sizeof(addr);

	if (getsockname(event.data.fd, (struct sockaddr*)&addr, &addrlen) < 0)
		return writeStreerrorPrefix("Server::configureEnvsServer: getsockname: ");
	_port = ntohs(addr.sin_port);
	_client_fd = event.data.fd;
	if (event.events & EPOLLOUT)
		_write = true;
	return true;
}

bool	Server::createNewResponses()
{
	if (_responses.find(_client_fd) != _responses.end())
	{
		_response = _responses.at(_client_fd);
		return true;
	}
	write_debug("createNewResponses");
	_responses.insert(std::pair<int, Response*>(_client_fd, new Response));
	_response = _responses.at(_client_fd);
	_response->write = _write;
	_response->port = _port;
	Server_configuration* configuration = _serversConf.at(_port);
	_response->errorPage = configuration->get_error_page();
	_response->root = configuration->get_root();
	_response->cgi = configuration->get_cgi();
	_response->locations = configuration->get_locations();
	_response->index = configuration->get_index();
	_response->autoindex = configuration->get_autoIndex();
	_response->clientMaxBodySize = configuration->get_clientMaxBodySize();
	return true;
}


bool	Server::findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint)
{
	size_t lastSlashPos;

	if (endPoint[endPoint.length() - 1] != '/')
		endPoint += "/";
	if (endPoint[0] == '/')
		endPoint.erase(0, 1);
	while (true)
	{
		if (locations.find(endPoint) != locations.end())
			return true;
		lastSlashPos = endPoint.find_last_of('/', endPoint.length() - 2);
		if (lastSlashPos == std::string::npos || lastSlashPos == 0)
			return false;
		endPoint.erase((lastSlashPos + 1));
	}
}

bool	Server::handleKeepAlive( void )
{
	std::string	typeConnection = getenv("HTTP_CONNECTION");
	if (typeConnection == "keep-alive")
		write_debug("Keep-Alive\n");
	else
	{
		write_debug_number("Close: ", _client_fd);
		cleanupFd(_client_fd);
	}
	return (true);
}

bool	Server::sendResponseClient(std::string response)
{
	write_debug("sendResponseClient");
	cleanupResponse(_client_fd);
	if (_write != true)
		return (true);
	if ((send(_client_fd, response.c_str(), response.size(), 0) < 0))
		return (write_error("Server::sendResponseClient: send"));
	return (handleKeepAlive());
}
