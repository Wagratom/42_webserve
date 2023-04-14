/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:47:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:25:25 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::dispatch_events(epoll_event* event)
{
	int	index;

	index = 0;
	while (index < number_of_events)
	{
		write_type_event_debug(event[index]);
		if (event[index].data.fd == server_fd)
		{
			if (!handle_new_connections(event[index]))
				return (false);
		}
		else
		{
			if (!handle_events(event[index]))
				return (false);
		}
		index++;
	}
	return (true);
}

int	Server::start_server( void )
{
	struct	epoll_event event[MAX_EVENTS];

	while (true)
	{
		if (!capture_new_events(event))
			return (-1);
		if (!dispatch_events(event))
			return (-1);
	}
}
