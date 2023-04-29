/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 10:36:20 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/socket.h>
# include <cstdio>
# include <netinet/in.h>
# include <iostream>
// # include <cstring>
# include <sys/epoll.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>

#include <parser.hpp>

#include <stdlib.h>

# define PORT 8080
# define MAX_EVENTS 10
# define MAX_CONNECTIONS 10

# define NOT_CONNECTION 0
# define NEW_CONNECTION 1

# define CHILD 0

class 	Server
{
	public:
		Server(std::string filename)
			: parser_file(new Parser_configuration(filename))
			, _aux_list_location(NULL)
			, _server_fd(-1)
		    , _epoll_fd(-1)
			, _number_of_events(-1)
			, _verbs(create_verbs())
		{};
		~Server() {
			delete this->parser_file;
		};

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
		bool	configured_child( epoll_event& event );
		bool	handle_request(epoll_event& event);
		bool	read_request( std::string& buffer,  epoll_event& event );

		bool	parse_request(std::string& buffer);
		bool	verift_error( int bytes_read );

		bool	clean_request(epoll_event& event);

		bool	write_error_prefix( std::string prefix );
		bool	fork_staus( pid_t& pid );

		//				GETTERS to tests
		t_location_settings*	location( void ) {
			return (this->parser_file->get_location_configuration());
		}

		t_location_settings*	get_aux_list_location( void ) {
			return (this->_aux_list_location);
		}

		void	set_aux_list_location( t_location_settings* tmp) {
			this->_aux_list_location = tmp;
		}
		server_configuration*	server( void ) {
			return (this->parser_file->get_server_configuration());
		}

		Parser_configuration*	get_parser( void ) {
			return (this->parser_file);
		}

		bool	setup( void );


		void	set_signal( void );

	private:
		Parser_configuration*	parser_file;
		Parser_request*			_parser_request;
		t_location_settings	*	_aux_list_location;
		list_file				*client_request;
		int						_server_fd;
		int						_epoll_fd;
		int						_number_of_events;

		std::string				**_verbs;
};

class Parser_request
{
	public:
		Parser_request( std::string& request_client );
		~Parser_request();

		bool	parse_requesition_line( std::string** verbs );

		bool	parse_requisition_line( void );
		bool	get_requesition_line( void );
		bool	get_verb( void );
		bool	valid_verb( std::string** verbs );
		bool	get_recurso( void );
		bool	valid_htpp_version( void );
		bool	write_error_prefix( std::string prefix );
		bool	write_msg_error(std::string message);
	private:
		std::string					_request;
		std::string					_order_request;
		std::string					_verb;
		std::string					_recurso;
};

void	set_debug(bool	value);
int		get_debug( void );
void	write_debug_number(std::string message, int number);
void	write_debug_prefix(std::string prefix, std::string message);
void	write_type_event_debug(epoll_event& event);
void	write_debug(std::string message);
