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

static void	savaDataCleint(epoll_event& event, int& port, int& client, bool& write)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen = sizeof(addr);

	getsockname(event.data.fd, (struct sockaddr*)&addr, &addrlen);
	port = ntohs(addr.sin_port);
	client = event.data.fd;
	write_debug_number("Port: ", port);
	write_debug_number("Client: ", client);
	if (event.events & EPOLLOUT)
		write = true;
}

bool	Server::handleClientRequest(epoll_event& event)
{
	std::string			buffer;

	write_debug("\nClient seed request");
	savaDataCleint(event, _port, _client_fd, _write);
	if (_response[_client_fd] != NULL)
		return handlePostBody();
	if (set_fdNotBlock(_client_fd) == false)
		return (false);
	if (readRequest(buffer) == false)
		return (false);
	if (responseRequest(buffer) == false)
		return (false);
	return (true);
}
