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
		write_error_prefixI("Client exit: ", event.data.fd);
	if (event.events & EPOLLERR)
		write_error_prefixI ("EPOLLERR fd: ", event.data.fd);
	else
		return (false);
	return (true);
}

bool	Server::handleEvents(epoll_event& event)
{
	write_debug("Handling events");
	if (isClosedOrErrorEvent(event))
		return cleanupFd(event.data.fd);
	if (event.events & EPOLLIN)
		return handleClientRequest(event);
	else
		return cleanupFd(event.data.fd);
	return (true);
}

