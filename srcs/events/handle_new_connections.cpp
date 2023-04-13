/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_new_connections.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 07:25:42 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

/*
EPOLL_CTL_ADD: Add a file descriptor to the interface.
EPOLL_CTL_MOD: Change file descriptor settings.
EPOLL_CTL_DEL: Remove a file descriptor from the interface.
*/

bool	is_new_connect(server& data, epoll_event* event)
{
	int	event_socket;

	event_socket = event->data.fd;
	if (data.server_fd == event_socket)
		return (true);
	return (false);
}

bool accept_status(int& server, int& server_fd)
{
	server_fd = accept(server, NULL, NULL);
	if (server_fd != -1)
		return (true);
	return (write_error_prefix("handle_new_connections"));
}

bool	save_connection(int& epoll_fd, int& server_fd)
{
	struct	epoll_event event;

	event = (struct epoll_event){0,0};
	event.data.fd = server_fd;
	event.events = EPOLLIN;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
		return (write_error_prefix("handle_new_connections"));
	return (true);
}

// bool	clear_epoll_event(int& epoll_fd, int& server_fd)
// {
// 	struct	epoll_event event;

// 	event.data.fd = server_fd;
// 	event.events = EPOLLIN;

// 	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, server_fd, &event) == -1)
// 		return (write_error_prefix("clear_epoll_event"));
// 	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
// 		return (write_error_prefix("clear_epoll_event"));
// 	std::cout << "eu\n";
// 	return (true);
// }

int	handle_new_connections(server& data, epoll_event* event)
{
	int		server_fd;

	if (!is_new_connect(data, event))
		return (0); // not a new connection
	if (!accept_status(data.server_fd, server_fd))
		return (-1); // error
	if (!save_connection(data.epoll_fd, server_fd))
		return (-1); // error
	// if (!clear_epoll_event(data.epoll_fd, server_fd))
	// 	return (-1); // error
	std::cout << "New connection accepted!" << std::endl;
	return (1); // success in create new connection
}

