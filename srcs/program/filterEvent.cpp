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

bool	Server::filterEvent(epoll_event* event)
{
	int	index;

	index = 0;
	while (index < _number_of_events)
	{
		write_type_event_debug(event[index]);
		if (event[index].data.fd == _server_fd)
		{
			if (!handleNewConnections(event[index]))
				return (false);
		}
		else
		{
			if (!handle_events(event[index]))
				return (false);
		}
		index++;
	}
	return (true);
}


bool	Server::handle_events(epoll_event& event)
{
	if (is_closed_or_error_event(event))
		return (cleanupFd(event));
	if (event.events & EPOLLIN)
		return (handle_client_request(event));
	else if (event.events & EPOLLOUT)
		return (cleanupFd(event));
	return (true);
}

bool	Server::is_closed_or_error_event(epoll_event& event)
{
	if (event.events & EPOLLERR)
		std::cout << "Error: error in connection" << std::endl;
	else if (event.events & EPOLLRDHUP)
		std::cout << "Error: abnormally closed connection" << std::endl;
	else if (event.events & EPOLLRDHUP)
		std::cout << "Client exit" << std::endl;
	else
		return (false);
	return (true);
}
