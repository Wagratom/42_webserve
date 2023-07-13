/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:47:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 10:48:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::checkTimeout( int& numberOfEvents )
{
	if (numberOfEvents > 0)
		return ;
	for (int i = 3; i < MAX_CLIENTS; i++)
		cleanupFd(i);
}

int	Server::startServer( void )
{
	struct	epoll_event event[MAX_EVENTS];

	write_debug("\033[0;36m\tStarting server\033[0;34m");
	while (true)
	{
		int	numberOfEvents = 0;
		if (!captureNewEvents(event, numberOfEvents))
			return (-1);
		checkTimeout(numberOfEvents);
		if (!filterEvent(event, numberOfEvents))
			return (-1);
		write_debug("\n");
	}
}
