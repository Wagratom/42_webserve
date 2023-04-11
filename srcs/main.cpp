/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 11:30:33 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	create_epoll(int& epoll_fd)
{
	epoll_fd = epoll_create(1);
	if (epoll_fd != -1)
		return (true);
	std::cout << "Error: an epoll_create()" << std::endl;
	return (false);
}

bool	create_epoll_configured(int& socket_fd, int& epoll_fd)
{
	if (create_epoll(epoll_fd))
		return (false);
	struct epoll_event event;
}

int main( void )
{
	int socket_fd;
	int	epoll_fd;

	if (create_server(socket_fd))
		return (1);
	if (create_epoll_configured(socket_fd, epoll_fd))
		return (1);
	return(0)

}


