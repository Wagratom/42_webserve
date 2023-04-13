/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 08:43:18 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

Server::Server( void ){};
Server::~Server( void ){};

int	main( void )
{
	Server data;

	if (!data.create_server_configured())
		return (-1);
	data.start_server();
	printf("to saindo");
	// close(data.epoll_fd);
	// close(data.server_fd);
	return (0);
}
