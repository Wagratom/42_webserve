/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClientRequest.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/01 13:44:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::savaDataCleint(epoll_event& event)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen = sizeof(addr);

	getsockname(event.data.fd, (struct sockaddr*)&addr, &addrlen);
	_port = ntohs(addr.sin_port);
	_client_fd = event.data.fd;
	write_debug_number("Port: ", _port);
	write_debug_number("Cleint: ", _client_fd);
	if (event.events & EPOLLOUT)
		_write = true;
	if (_responses.find(_client_fd) == _responses.end())
	{
		write_debug("Add new client in Client list");
		_responses.insert(std::pair<int, Response*>(_client_fd, NULL));
	}
}

bool	Server::handleClientRequest(epoll_event& event)
{
	std::string			buffer;

	write_debug("\nClient seed request");
	savaDataCleint(event);
	if (_responses.find(_client_fd)->second != NULL)
		return handlePostBody();
	if (set_fdNotBlock(_client_fd) == false)
		return (false);
	if (readRequest(buffer) == false)  // Fui na venda <-----------------
		return (false);
	if (responseRequest(buffer) == false)
		return (false);
	return (true);
}
