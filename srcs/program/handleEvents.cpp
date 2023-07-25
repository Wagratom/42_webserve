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

bool	Server::handleEvents(epoll_event& event)
{
	if (isClosedOrErrorEvent(event))
		return cleanupFd(event.data.fd);
	if (savaDataCleint(event) == false)
		cleanupFd(_client_fd);
	if (event.events & EPOLLIN)
		return handleRequestClient();
	else if (event.events & EPOLLOUT)
		return handleClientResponse();
	return (true);
}

