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

bool	Server::checkEventInServer(epoll_event event, int& serverFd)
{
	for (std::map<int, Server_configuration*>::iterator it = _serversConf.begin(); it != _serversConf.end(); it++)
	{
		if (it->first != event.data.fd)
			continue ;
		serverFd = it->first;
		return (true);
	}
	return (false);
}

bool	Server::filterEvent(epoll_event* event, int numberOfEvents)
{
	int	index;

	index = 0;
	while (index < numberOfEvents)
	{
		int serverFd = 0;
		if (checkEventInServer(event[index], serverFd))
			handleNewConnections(serverFd);
		else
			handleEvents(event[index]);
		index++;
	}
	return (true);
}
