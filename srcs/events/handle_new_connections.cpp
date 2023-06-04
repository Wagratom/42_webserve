/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_new_connections.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 13:46:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

// Flags for epoll_ctl()
/*
EPOLL_CTL_ADD: Add a file descriptor to the interface.
EPOLL_CTL_MOD: Change file descriptor settings.
EPOLL_CTL_DEL: Remove a file descriptor from the interface.
*/

// Flags for epoll_event.events
/*
EPOLLHUP: Indica que a outra extremidade da conexão fechou a conexão de maneira normal ou anormal, ou seja, um evento hang-up foi detectado na conexão.
EPOLLERR: Indica que ocorreu um erro na conexão.
EPOLLRDHUP: Indica que a outra extremidade da conexão fechou a conexão de maneira normal, ou seja, um evento hang-up foi detectado na conexão,
mas ainda há dados para ler. Isso pode acontecer, por exemplo, quando a outra extremidade faz um shutdown parcial da conexão, fechando a gravação,
mas ainda permitindo a leitura dos dados que já foram enviados.
*/

bool	Server::is_new_connect(epoll_event& event)
{
	int	event_socket;

	event_socket = event.data.fd;
	if (_server_fd == event_socket)
		return (true);
	return (false);
}

bool	Server::accept_status( int& new_client )
{
	new_client = accept(_server_fd, NULL, NULL);
	if (new_client == -1)
		return (write_error_prefix("accept_status"));
	// write_debug("\n\nNew connection accepted");
	return (true);
}

bool	Server::save_connection( int& new_client )
{
	struct	epoll_event event;

	event = (struct epoll_event){0,0};
	event.data.fd = new_client;
	event.events = EPOLLIN | EPOLLHUP | EPOLLRDHUP | EPOLLERR;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, new_client, &event) == -1)
		return (write_error_prefix("save_connection"));
	return (true);
}

bool	Server::handle_new_connections(epoll_event& event)
{
	int	new_client;

	if (!is_new_connect(event))
		return (false); // not a new connection
	if (!accept_status(new_client))
		return (false); // error
	if (!save_connection(new_client))
		return (false); // error
	write_debug("New connection accepted");
	return (true); // success in create new connection
}

