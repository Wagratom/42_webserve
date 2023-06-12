/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:07:54 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/12 10:44:31 by wwallas-         ###   ########.fr       */
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
		std::cout << "\t\033[0;31m\tDebug mode is on\033[0;37m" << std::endl;
	else
		std::cout << "\tDebug mode is off" << std::endl;
}

void	write_debug_number(std::string message, int number)
{
	if (!get_debug())
		return ;
	if (number != -1)
		std::cout << message << number << std::endl;
	else
		std::cout << message << std::endl;
}

void	write_debug(std::string message)
{
	if (!get_debug())
		return ;
	std::cout << message << std::endl;
}

void	write_debug_prefix(std::string prefix, std::string message)
{
	if (!get_debug())
		return ;
	std::cout << prefix << message << std::endl;
}

#include <arpa/inet.h>

void	write_type_event_debug(epoll_event& event)
{
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);

	getsockname(event.data.fd, (struct sockaddr*)&addr, &addrlen);

	if (get_debug() == false)
		return ;
    std::cout << "Local IP address: " << inet_ntoa(addr.sin_addr) << std::endl;
    std::cout << "Local port number: " << ntohs(addr.sin_port) << std::endl;
	std::cout << "Type of event: ";
	if (event.events & EPOLLERR)
		std::cout << "EPOLLERR | ";
	if (event.events & EPOLLRDHUP)
		std::cout << "EPOLLRDHUP | ";
	if (event.events & EPOLLRDHUP)
		std::cout << "EPOLLRDHUP | ";
	if (event.events & EPOLLIN)
		std::cout << "EPOLLIN | ";
	if (event.events & EPOLLOUT)
		std::cout << "EPOLLOUT | ";
	if (event.events & EPOLLHUP)
		std::cout << "EPOLLHUP | ";
	if (event.events & EPOLLPRI)
		std::cout << "EPOLLPRI ";
	std::cout << std::endl << std::endl;
}
