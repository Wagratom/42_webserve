/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 09:43:34 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

int main( void )
{
	server data;

	data = (server){0,0};
	if (!create_server_configured(data))
		return (-1);
	start_server(data);
	printf("to saindo");
	close(data.epoll_fd);
	close(data.server_fd);
	return (0);
	return (start_server(data));
}
