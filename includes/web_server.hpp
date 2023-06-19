/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 17:50:20 by wwallas-         ###   ########.fr       */
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

# define ERROR404 104
# define ERROR_BAD_REQUEST 100
# define ERROR_INTERNAL 200

# define CHILD_PROCESS 0

typedef struct s_ChildProcessInfo {
	int	fd[2];
	int	pid;
	int	status;
	int	exit_status;

} ChildProcessInfo;

struct aux_upload;

class	Server
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
			for (int i = 0; i < 10; i++) {
				delete _verbs[i];
			}
			delete [] _verbs;
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

		bool	set_client_not_block( void );
		bool	read_request( std::string& buffer );
		bool	response_request( std::string& buffer );
		bool	parse_order_request( std::string& buffer );

		bool	handle_GET_requesition( void );
		bool	handle_GET_requesition_html( std::string& endPoint );
		void	prepare_path_server(std::string& dst, std::string& path);
		bool	response_server( std::string status_code );
		bool	response_file( std::string& path );
		bool	response_location( std::string& path );
		bool	response_location(t_location_settings* location);
		bool	get_root_location(std::string& root, const std::string& path);

		bool	execute_cgi_in_chuild( s_ChildProcessInfo& tools_chuild );
		void	response_get( s_ChildProcessInfo& tools_chuild );

		bool	handle_POST_requesition( void );
		bool	handle_update( void );

		bool	handle_DELETE_requesition( void );
		bool	response_client_with_list_files( void );
		bool	processFileUpload( aux_upload& data );

		bool	generete_path_to_response( std::string& dst , std::string root, std::string listNames );
		bool	send_response_to_client( int& buffer_html );
		bool	sendErrorResponseToClient( int status );

		bool	DELETE_requesition( void );

		typedef	std::string(*header)( void );
		bool	sendErrorToClient( std::string path, header function );

		bool	closed_fd_epoll(epoll_event& event);

		bool	write_error_prefix( std::string prefix );

		bool	response_client( std::string response );

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

bool		get_content_file(aux_read_file& dst);
void		create_header_to_files(aux_read_file& tmp, std::string status_code);
std::string	create_header_html(std::string status_code);
std::string	create_header_404(void);
std::string	create_header_400( void );
std::string	create_header_500( void );
bool		isDirectory(const std::string& path);
bool		execute_fork( ChildProcessInfo& infos);
void		execute_cgi(char** argv, char** envp);
