/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/03 14:23:39 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Parser_request.hpp>
#include <Parser_configuration.hpp>

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
			: _parser_file(new Parser_configuration(filename))
			, _parser_request(NULL)
			, _aux_list_location(NULL)
			, _server_fd(-1)
		    , _epoll_fd(-1)
			, _number_of_events(-1)
			, _verbs(create_verbs())
		{};
		~Server() {
			delete _parser_file;
			if (_parser_request)
				delete _parser_request;
		};

		std::string**	create_verbs( void );

		bool	create_server_configured( void );
		bool	create_server( void );
		bool	create_socket( void );
		bool	set_socket_option( void );
		bool	bind_socket( void );
		bool	listen_socket( void );

		bool	conf_serve_to_read( void );
		bool	create_epoll( void );
		bool	add_mode_read( void );

		int		start_server( void );

		bool	capture_new_events( epoll_event* event );
		bool	filter_event( epoll_event* event );

		bool	handle_new_connections( epoll_event& event );
		bool	is_new_connect( epoll_event& event );
		bool	accept_status( int& new_client );
		bool	save_connection( int& new_client );

		bool	handle_events( epoll_event& event );
		bool	is_closed_or_error_event( epoll_event& event );
		bool	handle_client_request( epoll_event& event );

		bool	set_client_no_block( void );
		bool	read_request( std::string& buffer );
		bool	parse_request( std::string& buffer );
		bool	response_request( void );

		int		GET_requesition( void );
		bool	open_file_index( std::ifstream& file );
		bool	serv_webpage( std::ifstream& file);

		bool	SET_requesition( void );
		bool	DELETE_requesition( void );

		bool	closed_fd_epoll(epoll_event& event);

		bool	write_error_prefix( std::string prefix );

		bool	clean_request(epoll_event& event);

		//				GETTERS to tests
		t_location_settings*	location( void ) {
			return (this->_parser_file->get_location_configuration());
		}

		t_location_settings*	get_aux_list_location( void ) {
			return (this->_aux_list_location);
		}

		void	set_aux_list_location( t_location_settings* tmp) {
			this->_aux_list_location = tmp;
		}
		server_configuration*	server( void ) {
			return (this->_parser_file->get_server_configuration());
		}

		Parser_configuration*	get_parser( void ) {
			return (this->_parser_file);
		}

		bool	setup( void );


		void	set_signal( void );

	private:
		Parser_configuration*	_parser_file;
		Parser_request*			_parser_request;
		t_location_settings	*	_aux_list_location;

		int						_server_fd;
		int						_client_fd;
		int						_epoll_fd;

		int						_number_of_events;

		std::string				**_verbs;
};

void	set_debug(bool	value);
int		get_debug( void );
void	write_debug_number(std::string message, int number);
void	write_debug_prefix(std::string prefix, std::string message);
void	write_type_event_debug(epoll_event& event);
void	write_debug(std::string message);
