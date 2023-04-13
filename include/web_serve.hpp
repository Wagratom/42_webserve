/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_serve.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 14:05:18 by wwallas-         ###   ########.fr       */
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
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>


#include <stdlib.h>


# define PORT 8080
# define MAX_EVENTS 10
# define MAX_CONNECTIONS 10

# define NOT_CONNECTION 0
# define NEW_CONNECTION 1

# define CHILD 0

class Server
{
	public:
		Server();
		~Server();

		bool	create_server_configured( void );
		bool	create_server( void );
		bool	create_socket( void );
		bool	bind_socket( void );
		bool	listen_socket( void );

		bool	conf_serve_to_read( void );
		bool	create_epoll( void );
		bool	add_mode_read( void );

		int		start_server( void );

		bool	capture_new_events(epoll_event* event);
		bool	dispatch_events(epoll_event* event);
		bool	handle_events(epoll_event& event);


		bool	handle_new_connections(epoll_event& event);
		bool	is_new_connect(epoll_event& event);
		bool	accept_status( int& new_client );
		bool	save_connection( int& new_client );

		bool	handle_request(epoll_event& event);
		bool	separate_request_child(epoll_event& event);
		bool	conf_fd_to_not_block(epoll_event& event);
		bool	verift_error(int bytes_read);
		bool	read_request(std::string& buffer, epoll_event& event);

		bool	clean_request(epoll_event& event);

		bool	write_error_prefix(std::string prefix);
		bool	fork_staus(pid_t& pid);

		void	set_signal( void );

		static void	set_shutdown_server( int sig );

	private:
		int		server_fd;
		int		epoll_fd;
		int		number_of_events;
		bool	shutdown_server;
};

