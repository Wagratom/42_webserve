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

bool	Server::captureNewEvents(epoll_event* event)
{
	write_debug("Waiting for events");
	_number_of_events = epoll_wait(_epoll_fd, event, MAX_EVENTS, -1);
	write_debug_number("Number of captured events: ", _number_of_events);
	if (_number_of_events == -1)
		return (write_error_prefix("handle_new_connections"));
	return (true);
}
