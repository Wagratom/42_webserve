/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/28 12:42:01 by wwallas-         ###   ########.fr       */
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

# define ERROR400 100
# define ERROR404 104
# define ERROR413 113
# define ERROR415 115
# define ERROR500 200

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
		Server(std::string filename);
		~Server( void );

		std::string**	create_verbs( void );
		void			initializeDefaultErrorPage( void );

		bool	create_server_configured( void );
		bool	create_server( void );
		bool	createSockeConfigured( void );
		bool	bind_socket( void );
		bool	listen_socket( void );

		bool	conf_serve_to_read( void );
		bool	create_epoll( void );
		bool	add_mode_read( void );

		int		start_server( void );

		bool	captureNewEvents( epoll_event* event );
		bool	filterEvent( epoll_event* event );

		bool	handleNewConnections( epoll_event& event );
		bool	is_newConnect( epoll_event& event );
		bool	accept_status( int& new_client );
		bool	save_connection( int& new_client );

		bool	handle_events( epoll_event& event );
		bool	is_closed_or_error_event( epoll_event& event );
		bool	handle_client_request( epoll_event& event );

		bool	set_fdNotBlock( int& fd );
		bool	read_request( std::string& buffer );
		bool	response_request( std::string& buffer );
		bool	parse_order_request( std::string& buffer );

		bool	handle_GET_requesition( void );
		bool	responseClientGET( std::string& endPoint );
		bool	responseServer( std::string status_code );
		bool	responseAutoIndexOrErrorServer( void );
		bool	responseAutoIndexOrErrorLocation( t_location* location );

		bool	responseFileServer( std::string endPoint );
		bool	responseFileLocation(t_location* location, std::string endPoint);
		bool	responseLocation( std::string endPoint, std::string locationName );
		bool	returnIndexLocation(t_location* _location );
		bool	createRootLocation(std::string& dst, const t_location* location);

		bool	handle_POST_requesition( void );
		bool	responseClientPOST( aux_upload& data );

		bool	handle_DELETE_requesition( void );
		bool	responseClientListFiles( std::string pathDir, std::string pathFile );
		bool	processFileUpload( aux_upload& data );

		bool	generetePathToResponse( std::string& dst , std::string root, std::string listNames );
		bool	responseClientError( int status, std::string pathFileError );

		bool	sendErrorToClient( std::string path, std::string header );

		bool	closed_fd_epoll(epoll_event& event);

		bool	write_error_prefix( std::string prefix );

		bool	sendResponseClient( std::string response );

		bool	responseRedirect(std::string endPoint);
		bool	cleanupFd(epoll_event& event);

		std::string	getErrorPageMapServer(std::string Error);
		std::string	getErrorPageMapLocation(t_location* _location, std::string Error);
		//				GETTERS to tests
		std::map<std::string, t_location*>	location( void ) {
			return (this->_parserFile->get_location_configuration());
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

		int						_server_fd;
		int						_client_fd;
		int						_epoll_fd;
		int						_number_of_events;

		bool					_write;


		std::string				**_verbs;
		std::map<int, std::string>	_defaultErrorPage;
};

void	set_debug(bool	value);
int		get_debug( void );

bool		getContentFile(auxReadFiles& dst);
void		generateDynamicHeader(auxReadFiles& tmp, std::string status_code);
std::string	generateHeaderDynamicStatus(std::string status);
bool		executeFork( ChildProcessData& infos);
void		executeCGI(char** argv, char** envp);
bool		getContentFile(auxReadFiles& dst);
void		appendBar(std::string& str);
bool		getContentFilePHP(auxReadFiles& dst);
bool		generateFilesList(std::string& listFiles, const char* pathDir);
bool		generateResponse(std::string listFiles, std::string& response);
std::string	generateHeaderRedirect(std::string status, std::string endPoint);
