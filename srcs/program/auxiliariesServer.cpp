/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliariesServer.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/30 14:23:30 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

std::string	Server::getErrorPageMap(const std::map<std::string, std::string*>& errorMap, std::string error)
{
	if (error.empty())
		return ("");
	try {
		return (*errorMap.at(error));
	} catch (const std::exception& e) {
		return ("");
	}
}

std::string	get_stringError(int error)
{
	if (error == ERROR400) // Bad Request
		return ("400");
	if (error == ERROR403) // Forbidden
		return ("403");
	if (error == ERROR404) // Not Found
		return ("404");
	if (error == ERROR405) // Method Not Allowed
		return ("405");
	if (error == ERROR413) // Request Entity Too Large
		return ("413");
	if (error == ERROR500) // Internal Server Error
		return ("500");
	return ("");
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
	_serverUsing = _serversConf.at(_port);
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
	_responses.at(_client_fd)->write = _write;
	_responses.at(_client_fd)->port = _port;
	_response = _responses.at(_client_fd);
	return true;
}


bool	Server::findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint)
{
	size_t lastSlashPos;

	if (endPoint[endPoint.length() - 1] != '/')
		endPoint += "/";
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
