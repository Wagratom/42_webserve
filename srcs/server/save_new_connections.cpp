/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_new_connections.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 22:49:07 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	is_new_connect(server& data, epoll_event* event)
{
	int	event_socket;

	event_socket = event->data.fd;
	if (data.socket_fd == event_socket)
		return (true);
	return (false);
}

bool	save_connection(server& data)
{
	int		new_socket;
	struct	epoll_event event;


	new_socket = accept(data.socket_fd, NULL, NULL);
	event.data.fd = new_socket;
	event.events = EPOLLIN | EPOLLOUT;
	if (epoll_ctl(data.epoll_fd, EPOLL_CTL_ADD, new_socket, &event) == -1)
		return (write_error_prefix("save_new_connections"));
	return (true);
}

bool	save_new_connections(server& data, epoll_event* event)
{

	if (!is_new_connect(data, event))
		return (false);
	if (!save_connection(data))
		return (false);
	return (true);
}

