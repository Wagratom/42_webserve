/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:07:54 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:25:56 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool&	debug()
{
	static bool debug = false;
	return (debug);
}

int	get_debug()
{
	return (debug());
}

void	set_debug(bool	value)
{
	debug() = value;
	if (value == true)
		std::cout << "\tDebug mode is on" << std::endl;
	else
		std::cout << "\tDebug mode is off" << std::endl;
}

void	write_debug(std::string message, int number)
{
	if (!get_debug())
		return ;
	if (number != -1)
		std::cout << message << number << std::endl;
	else
		std::cout << message << std::endl;
}

void	write_type_event_debug(epoll_event& event)
{
	std::cout << "\tType of event" << std::endl;
	if (get_debug() == false)
		return ;
	if (event.events & EPOLLERR)
		std::cout << "Event: EPOLLERR" << std::endl;
	else if (event.events & EPOLLRDHUP)
		std::cout << "Event: EPOLLRDHUP" << std::endl;
	else if (event.events & EPOLLRDHUP)
		std::cout << "Event: EPOLLRDHUP" << std::endl;
	else if (event.events & EPOLLIN)
		std::cout << "Event: EPOLLIN" << std::endl;
	else if (event.events & EPOLLOUT)
		std::cout << "Event: EPOLLOUT" << std::endl;
	else if (event.events & EPOLLHUP)
		std::cout << "Event: EPOLLHUP" << std::endl;
	else if (event.events & EPOLLPRI)
		std::cout << "Event: EPOLLPRI" << std::endl;
}
