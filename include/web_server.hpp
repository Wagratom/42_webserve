/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 21:52:09 by wwallas-         ###   ########.fr       */
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

		std::string**	create_verbs( void );

		bool	create_server_configured( void );
		bool	create_server( void );
		bool	create_socket( void );
		bool	bind_socket( void );
		bool	listen_socket( void );

		bool	conf_serve_to_read( void );
		bool	create_epoll( void );
		bool	add_mode_read( void );

		int		start_server( void );

		bool	capture_new_events( epoll_event* event );
		bool	dispatch_events( epoll_event* event );

		bool	handle_new_connections( epoll_event& event );
		bool	is_new_connect( epoll_event& event );
		bool	accept_status( int& new_client );
		bool	save_connection( int& new_client );

		bool	handle_events( epoll_event& event );
		bool	is_closed_or_error_event( epoll_event& event );
		bool	send_request_to_child( epoll_event& event );

		void	handle_request_in_child( epoll_event& event );
		bool	conf_fd_to_not_block( epoll_event& event );
		bool	handle_request(epoll_event& event);
		bool	read_request( std::string& buffer,  epoll_event& event );

		bool	parse_request(std::string& buffer);
		bool	verift_error( int bytes_read );

		bool	clean_request(epoll_event& event);

		bool	write_error_prefix( std::string prefix );
		bool	fork_staus( pid_t& pid );

		void	set_signal( void );

		static void	set_shutdown_server( int sig );

	private:
		int			server_fd;
		int			epoll_fd;
		int			number_of_events;

		std::string	**verbs;
		bool	shutdown_server;
};

class Parser
{
	public:
		Parser(std::string const* const* verbs, std::string& requisition_line);
		~Parser();

		bool	parse_requesition_line( void );

		bool	parse_requisition_line( void );
		bool	get_line(std::string& line);
		bool	get_verb(std::string& line, std::string& verb);
		bool	valid_verb(std::string& verb);

		bool	write_msg_error(std::string message);
	private:
		std::string const* const* verbs;
		std::string			requesition;





};
void	set_debug(bool	value);
int		get_debug( void );
void	write_debug_number(std::string message, int number);
void	write_debug_prefix(std::string prefix, std::string message);
void	write_type_event_debug(epoll_event& event);
void	write_debug(std::string message);
