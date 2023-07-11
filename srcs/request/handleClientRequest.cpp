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

bool	Server::handleClientRequest(epoll_event& event)
{
	struct sockaddr_in	addr;
	std::string			buffer;
	socklen_t			addrlen = sizeof(addr);

	getsockname(event.data.fd, (struct sockaddr*)&addr, &addrlen);
	_port = ntohs(addr.sin_port);
	std::cout << "Port: " << _port << "|" << std::endl;

	write_debug("\nClient seed request");
	// if (event.events & EPOLLOUT)
	_write = true;
	_client_fd = event.data.fd;
	if (_response[_client_fd] != NULL)
		return handlePostRequest();
	if (set_fdNotBlock(_client_fd) == false)
		return (false);
	if (readRequest(buffer) == false)
		return (false);
	if (responseRequest(buffer) == false)
		return (false);
	return (true);
}
