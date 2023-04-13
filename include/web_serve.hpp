/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_serve.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 22:12:14 by wwallas-         ###   ########.fr       */
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
#include <unistd.h>
       #include <fcntl.h>


#include <stdlib.h>


# define PORT 8080
# define MAX_EVENTS 10
# define MAX_CONNECTIONS 10

# define NOT_NEW_CONNECTION 0

# define CHILD 0

typedef struct server
{
	int	server_fd;
	int	epoll_fd;
}				server;

bool	create_server_configured(server& data);
bool	create_server(server& data);
bool	conf_serve_to_read(server& data);
int		start_server(server& data);

bool	capture_new_events(int& epoll_fd, epoll_event* event);
bool	handle_events(server& data, epoll_event* event);
int		handle_new_connections(server& data, epoll_event* event);
bool	separate_request_child(server& data, epoll_event* event);
bool	handle_request(epoll_event* event);

bool	write_error_prefix(std::string prefix);
bool	fork_staus(pid_t& pid);
