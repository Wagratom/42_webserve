/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_serve.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 22:46:43 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/socket.h>
# include <cstdio>
# include <netinet/in.h>
# include <iostream>
# include <cstring>
# include <sys/epoll.h>
# include <errno.h>

typedef struct server
{
	int	socket_fd;
	int	epoll_fd;
}				server;

bool	create_server(server& data);
bool	conf_serve_to_read(server& data);
int		main_loop(server& data);
bool	save_new_connections(server& data, epoll_event* event);


bool	write_error_prefix(std::string prefix);
