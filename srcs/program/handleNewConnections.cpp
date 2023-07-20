/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleNewConnections.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 14:35:09 by wwallas-         ###   ########.fr       */
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

bool	Server::accept_status( int& new_client, int& serverFD )
{
	new_client = accept(serverFD, NULL, NULL);
	if (new_client == -1)
		return (writeStreerrorPrefix("Error: accept_status"));
	write_debug_number("New connection accepted: ", new_client);
	return (true);
}

bool	Server::save_connection( int& new_client )
{
	struct	epoll_event event;

	event = (struct epoll_event){0,0};
	event.data.fd = new_client;
	event.events = EPOLLIN | EPOLLHUP | EPOLLOUT | EPOLLRDHUP | EPOLLERR;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, new_client, &event) == -1)
		return (writeStreerrorPrefix("save_connection"));
	return (true);
}

bool	Server::handleNewConnections(int& serverFd)
{
	int	new_client;

	if (!accept_status(new_client, serverFd))
		return (false);
	if (!save_connection(new_client))
		return (false);
	return (true);
}
