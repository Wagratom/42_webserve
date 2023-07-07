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
	std::string	buffer;

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
	if (response_request(buffer) == false)
		return (false);
	// cleanupFd(event);
	return (true);
}
