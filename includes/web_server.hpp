/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 09:54:32 by wwallas-         ###   ########.fr       */
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

# define PATH_CGI "/usr/bin/php-cgi"
# define PATH_UPLOAD "/uploads/"
# define AUTO_INDEX "./root/autoindex.php"

#define MAX_SIZE_HEADER 1000000

class	Response
{
	public:
		Response( void ) : contentLenght(0), bytesRead(0), totalBytesRead(0), hasProcess(false), endProcess(false) {};
	public:
		int					contentLenght;
		int					bytesRead;
		int					totalBytesRead;
		int					fd[2];
		pid_t				pid;
		bool				hasProcess;
		bool				endProcess;
};

class	Server
{
	public:
		Server(std::string filename);
		~Server( void );

		std::string**	create_verbs( void );
		void			initializeDefaultErrorPage( void );
		// void			initializeResponses( void );


		bool	initializeServer( void );
		bool	createServerConfigured( void );
		bool	create_server( int& serverFd, Server_configuration* server );
		bool	createSockeConfigured( int& serverFd );
		bool	bind_socket( int& serverFd, Server_configuration* server );
		bool	listen_socket( int& serverFd );

		bool	create_epoll( void );
		bool	conf_serve_to_read( int& serverFD );
		bool	add_mode_read( int& serverFD );

		int		startServer( void );
		bool	captureNewEvents( epoll_event* event );
		bool	filterEvent( epoll_event* event );
		bool	checkEventInServer(epoll_event	event, int& serverFd);

		bool	handleNewConnections( int& serverFd );
		// bool	is_newConnect( epoll_event& event, int& serverFd);
		bool	accept_status( int& new_client, int& serverFD );
		bool	save_connection( int& new_client );

		bool	handleEvents( epoll_event& event );
		bool	is_closed_or_error_event( epoll_event& event );
		bool	handleClientRequest( epoll_event& event );

		bool	set_fdNotBlock( int& fd );
		bool	readRequest( std::string& buffer );
		bool	responseRequest( std::string& buffer );
		bool	deleteParserRequest(bool status);

		bool	handle_GET_requesition( void );
		bool	responseClientGET( std::string& endPoint );
		bool	responseServer( std::string status_code );
		bool	responseAutoIndexOrErrorServer( void );
		bool	responseAutoIndexOrErrorLocation( t_location* location );
		bool	responseInputGET(std::string endPoint);


		bool	responseFileServer( std::string endPoint );
		bool	responseFileLocation(t_location* location, std::string endPoint);
		bool	responseLocation( std::string endPoint, std::string locationName );
		bool	returnIndexLocation(t_location* _location );
		bool	createRootLocation(std::string& dst, const t_location* location);

		bool	handlePostRequest( void );
		bool	validatePostRequest( void );
		bool	handlePostBody( void );
		bool	readAndSaveBytes(Response* response, std::vector<char>& buffer);
		void	handleProcessPOST( Response* response, std::vector<char>& buffer );
		bool	redirectBodyCGI( Response* response, std::vector<char>& buffer );


		bool	handle_DELETE_requesition( void );
		bool	responseClientListFiles( std::string pathDir, std::string pathFile );
		// bool	extractFileNameFromBody( aux_upload& data );

		bool	generetePathToResponse( std::string& dst , std::string root, std::string listNames );
		bool	responseClientError( int status, std::string pathFileError );

		bool	sendErrorToClient( std::string path, std::string header );

		bool	closed_fd_epoll(epoll_event& event);

		bool	write_error_prefix( std::string prefix );

		bool	sendResponseClient( std::string response );

		bool	responseRedirect(std::string endPoint);
		bool	cleanupFd(int fd);

		std::string	getErrorPageMapServer(std::string Error);
		std::string	getErrorPageMapLocation(t_location* _location, std::string Error);
		//				GETTERS to tests
		std::map<std::string, t_location*>	location( int port ) {
			return (this->_serversConf[port]->get_locations());
		}

		std::vector<Server_configuration*>	server( void ) {
			return (this->_parserFile->get_server_configuration());
		}

		Parser_configuration*	get_parser( void ) {
			return (this->_parserFile);
		}


	private:
		Parser_configuration*	_parserFile;
		Parser_request*			_parserRequest;

		bool					_write;
		int						_client_fd;
		int						_epoll_fd;
		int						_number_of_events;

		Response				**_response;
		std::string				**_verbs;

		int										_port;
		std::map<int, Server_configuration*>	_serversConf;
		std::map<int, std::string>				_defaultErrorPage;
};

void		set_debug(bool	value);
int			get_debug( void );

bool		getContentFile(auxReadFiles& dst);
void		generateDynamicHeader(auxReadFiles& tmp, std::string status_code);
std::string	generateHeaderDynamicStatus(auxReadFiles& tmp, std::string status);
bool		executeFork( ChildProcessData& infos);
// void		executeCGI(char** argv, char** envp);
// bool		getContentFile(auxReadFiles& dst);
void		appendBar(std::string& str);
bool		getContentFilePHP(auxReadFiles& dst);
bool		generateFilesList(std::string& listFiles, const char* pathDir);
bool		generateResponse(std::string& response);
std::string	generateHeaderRedirect(std::string status, std::string endPoint);
bool		readOuputFormatedCGI(ChildProcessData& auxProcess, std::string& oss);
