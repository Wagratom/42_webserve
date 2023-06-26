/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client_request.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 12:02:39 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_client_request(epoll_event& event)
{
	std::string	buffer;

	write_debug("\nClient seed request");
	_write = true;
	// if (event.events & EPOLLOUT)
	_client_fd = event.data.fd;
	if (set_fdNotBlock(_client_fd) == false)
		return (false);
	if (read_request(buffer) == false)
		return (false);
	if (response_request(buffer) == false)
		return (false);
	cleanupFd(event);
	return (true);
}
