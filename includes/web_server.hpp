/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 10:48:52 by wwallas-         ###   ########.fr       */
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
# define ERROR415 115
# define ERROR_BAD_REQUEST 100
# define ERROR_INTERNAL 200

# define CHILD_PROCESS 0

typedef struct s_ChildProcessInfo {
	int	fd[2];
	int	pid;
	int	status;
	int	exit_status;

} ChildProcessData;

struct aux_upload;

class	Server
{
	public:
		Server(std::string filename)
			: _parserFile(new Parser_configuration(filename))
			, _parserRequest(NULL)
			, _aux_list_location(NULL)
			, _server_fd(-1)
			, _epoll_fd(-1)
			, _number_of_events(-1)
			, _verbs(create_verbs())
		{};
		~Server() {
			delete _parserFile;
			for (int i = 0; i < 10; i++) {
				delete _verbs[i];
			}
			delete [] _verbs;
			if (_parserRequest)
				delete _parserRequest;
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

		bool	captureNewEvents( epoll_event* event );
		bool	filterEvent( epoll_event* event );

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
		bool	responseClientGET( std::string& endPoint );
		bool	responseServer( std::string status_code );
		bool	responseFile( std::string endPoint );
		bool	responseLocation( std::string endPoint );
		bool	createRootLocation(std::string& dst, const t_location* location);

		bool	handle_POST_requesition( void );
		bool	responseClientPOST( aux_upload& data );

		bool	handle_DELETE_requesition( void );
		bool	responseClientDELETE( void );
		bool	processFileUpload( aux_upload& data );

		bool	generetePathToResponse( std::string& dst , std::string root, std::string listNames );
		bool	responseClientError( int status );

		bool	sendErrorToClient( std::string path, std::string header );

		bool	closed_fd_epoll(epoll_event& event);

		bool	write_error_prefix( std::string prefix );

		bool	sendResponseClient( std::string response );

		bool	clean_request(epoll_event& event);

		//				GETTERS to tests
		std::map<std::string, t_location*>	location( void ) {
			return (this->_parserFile->get_location_configuration());
		}

		t_location*	get_aux_list_location( void ) {
			return (this->_aux_list_location);
		}

		void	set_aux_list_location( t_location* tmp) {
			this->_aux_list_location = tmp;
		}
		server_configuration*	server( void ) {
			return (this->_parserFile->get_server_configuration());
		}

		Parser_configuration*	get_parser( void ) {
			return (this->_parserFile);
		}

		bool	startServer( void );

	private:
		Parser_configuration*	_parserFile;
		Parser_request*			_parserRequest;
		t_location	*	_aux_list_location;

		int						_server_fd;
		int						_client_fd;
		int						_epoll_fd;

		int						_number_of_events;

		std::string				**_verbs;
};

void	set_debug(bool	value);
int		get_debug( void );

bool		getContentFile(auxReadFiles& dst);
void		generateDynamicHeader(auxReadFiles& tmp, std::string status_code);
std::string	generateHeaderDynamicStatus(std::string status);
bool		isDirectory(const std::string& path);
bool		executeFork( ChildProcessData& infos);
void		executeCGI(char** argv, char** envp);
bool		getContentFile(auxReadFiles& dst);
void		appendBar(std::string& str);
bool		getContentFilePHP(auxReadFiles& dst);
bool		generateFilesList(std::string& listFiles);
bool		generateResponse(std::string listFiles, std::string& response);
