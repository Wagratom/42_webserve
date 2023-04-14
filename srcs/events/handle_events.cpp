/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 21:57:24 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

// bool	Server::clean_request(epoll_event& event)
// {
// 	std::cout << "removendo fd do epoll" << std::endl;
// 	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event.data.fd, NULL) == -1)
// 		return (write_error_prefix("remove_fd_from_epoll"));
// 	close(event.data.fd);
// 	return (true);
// }


bool	Server::capture_new_events(epoll_event* event)
{
	std::cout << "Waiting for new events..." << std::endl;
	number_of_events = epoll_wait(epoll_fd, event, MAX_EVENTS, -1);
	std::cout << "Number of events received:: " << number_of_events << std::endl;
	if (number_of_events == -1)
		return (write_error_prefix("handle_new_connections"));
	return (true);
}

bool	Server::is_closed_or_error(epoll_event& event)
{
	if (event.events & EPOLLERR)
		std::cout << "Error: error in connection" << std::endl;
	else if (event.events & EPOLLRDHUP)
		std::cout << "Error: abnormally closed connection" << std::endl;
	else if (event.events & EPOLLRDHUP)
		std::cout << "Client exit" << std::endl;
	else
		return (false);
	return (true);
}

bool	Server::handle_events(epoll_event& event)
{
	if (is_closed_or_error(event))
		return (true);
	if (event.events & EPOLLIN)
		return (separate_request_child(event));
	return (true);
}
