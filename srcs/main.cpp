/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:15:24 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

Server::Server( void ){};
Server::~Server( void ) {
	epoll_ctl(epoll_fd, EPOLL_CTL_DEL, server_fd, NULL);
	close(epoll_fd);
	close(server_fd);
};

int	main( void )
{
	Server data;

	set_debug(true);
	data.set_signal();
	if (!data.create_server_configured())
		return (-1);
	data.start_server();
	printf("to saindo");
	// close(data.epoll_fd);
	// close(data.server_fd);
	return (0);
}
