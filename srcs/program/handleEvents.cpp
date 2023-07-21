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

bool	Server::isClosedOrErrorEvent(epoll_event& event)
{
	if (event.events & EPOLLRDHUP)
		write_debug_number("Client exit: ", event.data.fd);
	else if (event.events & EPOLLERR)
		write_error_prefixI ("EPOLLERR fd: ", event.data.fd);
	else
		return (false);
	return (true);
}

bool	Server::handleClientResponse( void )
{
	write_debug_number("handleClientResponse: ", _client_fd);
	if (_responses.find(_client_fd) == _responses.end())
		return cleanupFd(_client_fd);
	if (waitpid(_responses.at(_client_fd)->process.pid, NULL, WNOHANG) == 0)
		return (true);
	if (_responses.at(_client_fd)->method == "GET")
	{
		std::string	content;

		if (readOuputFormatedCGI(content, _responses.at(_client_fd)->process) == false)
			responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500"));
		sendResponseClient(content);
	}
	else
		responseServer();
	cleanupFd(_client_fd);
	cleanupResponse(_client_fd);
	return (true);
}

bool	Server::handleEvents(epoll_event& event)
{
	if (isClosedOrErrorEvent(event))
		return cleanupFd(event.data.fd);
	if (savaDataCleint(event) == false)
		cleanupFd(_client_fd);
	if (event.events & EPOLLIN)
		return handleClientRequest();
	else if (event.events & EPOLLOUT)
		return handleClientResponse();
	return (true);
}

