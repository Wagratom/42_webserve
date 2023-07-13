/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captureNewEvents.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/13 15:19:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::captureNewEvents(epoll_event* event, int& numberOfEvents)
{
	write_debug("Waiting for events");
	numberOfEvents = epoll_wait(_epoll_fd, event, MAX_EVENTS, 100000);
	write_debug_number("Number of captured events: ", numberOfEvents);
	if (numberOfEvents == -1)
		return (writeStreerrorPrefix("handleNewConnections"));
	return (true);
}
