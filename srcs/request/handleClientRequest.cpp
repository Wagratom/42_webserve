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

bool	Server::savaDataCleint(epoll_event& event)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen = sizeof(addr);

	try {
		getsockname(event.data.fd, (struct sockaddr*)&addr, &addrlen);
		_port = ntohs(addr.sin_port);
		_client_fd = event.data.fd;
		if (event.events & EPOLLOUT)
			_write = true;
		_serverUsing = _serversConf.at(_port);
		return (true);
	} catch (std::exception& e) {
		return  write_error("handle_GET_requesition: " + std::string(e.what()));
	}
}

bool	Server::handleClientRequest( void )
{
	std::string			buffer;

	write_debug_number("handleClientRequest: ", _client_fd);
	if (_responses.find(_client_fd) != _responses.end())
		return handlePostBody();
	if (readRequest(buffer) == false)  // Fui na venda <-----------------
		return (false);
	if (responseRequest(buffer) == false)
		return (false);
	return (true);
}
