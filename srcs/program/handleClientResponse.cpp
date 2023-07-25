/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filterEvent.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 10:44:18 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handleProcessClient(const Response* response)
{
	if (response->method == "GET")
	{
		std::string	content;

		_serverUsing = _serversConf.at(response->port);
		if (readOuputFormatedCGI(content, response->process) == false)
			responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(response->errorMap, "500"));
		sendResponseClient(content);
	}
	else
		responseServer();
	cleanupFd(_client_fd);
	cleanupResponse(_client_fd);
	return (true);
}

bool	Server::handleClientResponse( void )
{
	std::map<int, Response*>::iterator itClient = _responses.find(_client_fd);

	write_debug_number("handleClientResponse: ", _client_fd);
	if (itClient == _responses.end())
		return cleanupFd(_client_fd);
	if (waitpid(itClient->second->process.pid, NULL, WNOHANG) == 0)
		return (true);
	_client_fd = itClient->first;
	return (handleProcessClient(itClient->second));
}
