/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 08:24:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	capture_new_events(server& data, epoll_event* event)
{
	int	numb_events;

	std::cout << "Waiting for new events..." << std::endl;
	numb_events = epoll_wait(data.epoll_fd, event, MAX_EVENTS, -1);
	std::cout << "Number of events received:: " << numb_events << std::endl;
	if (numb_events == -1)
		return (write_error_prefix("handle_new_connections"));
	return (true);
}

bool	clean_request(int& epoll_fd, epoll_event* event)
{
	std::cout << "removendo fd do epoll" << std::endl;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event[0].data.fd, NULL) == -1)
		return (write_error_prefix("remove_fd_from_epoll"));
	close(event->data.fd);
	return (true);
}

bool	handle_events(server& data, epoll_event* event)
{
	int	status;

	status = handle_new_connections(data, event);
	if (status == -1)
		return (false);
	if (status == NOT_NEW_CONNECTION)
	{
		if (!separate_request_child(data, event))
			return (false);
		if (!clean_request(data.epoll_fd, event))
			return (false);
	}
	return (true);
}
