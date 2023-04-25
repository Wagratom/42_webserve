/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/16 16:07:13 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::clean_request(epoll_event& event)
{
	std::cout << "removendo fd do epoll" << std::endl;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event.data.fd, NULL) == -1)
		return (write_error_prefix("remove_fd_from_epoll"));
	close(event.data.fd);
	return (true);
}

bool	Server::capture_new_events(epoll_event* event)
{
	number_of_events = epoll_wait(epoll_fd, event, MAX_EVENTS, -1);
	write_debug_number("Number of events received:: ", number_of_events);
	if (number_of_events == -1)
		return (write_error_prefix("handle_new_connections"));
	return (true);
}

bool	Server::dispatch_events(epoll_event* event)
{
	int	index;

	index = 0;
	while (index < number_of_events)
	{
		write_type_event_debug(event[index]);
		if (event[index].data.fd == server_fd)
		{
			if (!handle_new_connections(event[index]))
				return (false);
		}
		else
		{
			if (!handle_events(event[index]))
				return (false);
			clean_request(event[index]);
		}
		index++;
	}
	return (true);
}

bool	Server::handle_events(epoll_event& event)
{
	if (is_closed_or_error_event(event))
		return (true);
	if (event.events & EPOLLIN)
		return (send_request_to_child(event));
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

bool	Server::send_request_to_child(epoll_event& event)
{
	pid_t	pid;

	if (!fork_staus(pid))
		return (false);
	if (pid == CHILD)
		handle_request_in_child(event);
	return (true);
}
