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

bool static	checkEventInServer(epoll_event event, const std::map<int, Server_configuration*>& serversConf)
{
	if (serversConf.find(event.data.fd) != serversConf.end())
		return (true);
	return (false);
}

bool	Server::filterEvent(epoll_event* event, int numberOfEvents)
{
	int	index;

	index = 0;
	while (index < numberOfEvents)
	{
		if (checkEventInServer(event[index], _serversConf))
			handleNewConnections(event[index].data.fd);
		else
		{
			if (handleEvents(event[index]) == false)
				cleanupClient(_client_fd);
		}
		index++;
	}
	return (true);
}
