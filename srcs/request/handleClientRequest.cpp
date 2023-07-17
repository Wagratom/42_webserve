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
	if (event.events & EPOLLOUT)
		_write = true;
}

bool	Server::handleClientRequest(epoll_event& event)
{
	std::string			buffer;

	write_debug("\nClient seed request");
	savaDataCleint(event);
	if (_responses.find(_client_fd) != _responses.end())
		return handlePostBody();
	if (set_fdNotBlock(_client_fd) == false)
		return (false);
	if (readRequest(buffer) == false)  // Fui na venda <-----------------
		return (false);
	if (responseRequest(buffer) == false)
		return (false);
	return (true);
}
