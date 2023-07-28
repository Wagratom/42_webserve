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

bool	Server::handleProcessClient( void )
{
	write_debug("Generete response to client process");
	_response->hasProcess = false;
	std::string	content;

	_serverUsing = _serversConf.at(_response->port);
	if (readOuputFormatedCGI(content, _response->process) == false)
		responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "500"));
	sendResponseClient(content);
	// cleanupFd(_client_fd);
	return (true);
}

bool	Server::handleClientResponse( void )
{
	if (_response->hasProcess == false)
		return cleanupClient(_client_fd);
	if (waitpid(_response->process.pid, NULL, WNOHANG) == 0)
		return (true);
	return (handleProcessClient());
}
