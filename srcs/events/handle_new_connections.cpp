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

bool	Server::is_new_connect(epoll_event* event)
{
	int	event_socket;

	event_socket = event->data.fd;
	if (server_fd == event_socket)
		return (true);
	return (false);
}

bool	Server::accept_status( int& new_client )
{
	new_client = accept(server_fd, NULL, NULL);
	if (new_client != -1)
		return (true);
	return (write_error_prefix("handle_new_connections"));
}

bool	Server::save_connection( int& new_client )
{
	struct	epoll_event event;

	event = (struct epoll_event){0,0};
	event.data.fd = new_client;
	event.events = EPOLLIN;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_client, &event) == -1)
		return (write_error_prefix("handle_new_connections"));
	return (true);
}

// bool	Server::clear_epoll_event(int& epoll_fd, int& server_fd)
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

int	Server::handle_new_connections(epoll_event* event)
{
	int	new_client;

	if (!is_new_connect(event))
		return (0); // not a new connection
	if (!accept_status(new_client))
		return (-1); // error
	if (!save_connection(new_client))
		return (-1); // error
	// if (!clear_epoll_event(epoll_fd, server_fd))
	// 	return (-1); // error
	std::cout << "New connection accepted!" << std::endl;
	return (1); // success in create new connection
}

