/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 10:39:58 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

int main( void )
{
	int socket_desc;
	int	epoll_fd;

	if (create_server(socket_desc))
		return (1);
	if (create_epoll(epoll_fd))
		return (1);
	return(0)

}


