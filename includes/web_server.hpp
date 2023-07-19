/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/19 12:25:47 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Parser_request.hpp>
#include <Parser_configuration.hpp>
#include <ctime>

# define PORT 8080
# define MAX_EVENTS 10
# define MAX_CONNECTIONS 10
# define MAX_CLIENTS 1024

# define NOT_CONNECTION 0
# define NEW_CONNECTION 1

# define CHILD 0

# define ERROR400 100 // Bad Request
# define ERROR403 103 // Forbidden
# define ERROR404 104 // Not Found
# define ERROR405 105 // Method Not Allowed
# define ERROR413 113 // Payload Too Large
# define ERROR415 115 // Unsupported Media Type
# define ERROR500 200 // Internal Server Error
# define ERROR504 204 // Gateway Timeout

# define CHILD_PROCESS 0

# define PATH_CGI "/usr/bin/php-cgi"
# define PATH_UPLOAD "/uploads/"
# define AUTO_INDEX "./autoindex.php"

#define MAX_SIZE_HEADER 1000000


class	Response
{
	public:
		Response( void )
		: contentLenght(0)
		, bytesRead(0)
		, totalBytesRead(0)
		, hasProcess(false)
		, write(false)
		, creationTime(std::time(NULL)) {};

	public:
		int					contentLenght;
		int					bytesRead;
		int					totalBytesRead;
		ChildProcessData	process;
		bool				hasProcess;
		bool				write;
		std::time_t			creationTime;
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
		bool	createServer( int& serverFd, Server_configuration* server );
		bool	createSockeConfigured( int& serverFd );
		bool	bind_socket( int& serverFd, Server_configuration* server );
		bool	listen_socket( int& serverFd );

		bool	create_epoll( void );
		bool	confServeToRead( int& serverFD );
		bool	add_mode_read( int& serverFD );

		int		startServer( void );
		bool	captureNewEvents( epoll_event* event, int& numberOfEvents );
		bool	filterEvent( epoll_event* event, int numberOfEvents );
		void	checkTimeout( int& numberOfEvents );


		bool	checkEventInServer(epoll_event	event, int& serverFd);

		bool	handleNewConnections( int& serverFd );
		// bool	is_newConnect( epoll_event& event, int& serverFd);
		bool	accept_status( int& new_client, int& serverFD );
		bool	save_connection( int& new_client );

		bool	handleEvents( epoll_event& event );

		bool	isClosedOrErrorEvent( epoll_event& event );

		//		handleClientRequest
		bool	handleClientRequest( epoll_event& event );
		bool	savaDataCleint( epoll_event& event );
		bool	set_fdNotBlock( int& fd );
		bool	readRequest( std::string& buffer );
		bool	responseRequest( std::string& buffer );

		bool	handle_GET_requesition( void );
		bool	responseClientGET( std::string& endPoint );
		void	handleQuerystring(std::string& endPoint);
		bool	responseServer( void );
		bool	get_autoindex( const bool& autoindex, const std::string& root);

		bool	responseFileServer( std::string& endPoint );
		bool	preparingToReadFile(auxReadFiles& tmp, std::string& endPoint);

		bool	responseLocation( std::string& endPoint, std::string& locationName );
		bool	responseLocationPost(const t_location*& location);
		bool	responseFileLocation(const t_location*& location, std::string& endPoint);
		bool	returnIndexLocation(const t_location*& _location );
		bool	createRootLocation(const t_location*& location);

		bool	handlePostRequest( void );
		bool	handleScriptPOST( void );
		bool	checkPermitionFile(std::string path);
		bool	createValidResponse( void );
		bool	auxSendErrorPost( int status, std::string Error );
		bool	handlePostBody( void );
		bool	readAndSaveDatas(Response*& response, std::vector<char>& buffer);
		bool	createProcessResponse( Response*& response );
		void	handleProcessPOST( Response*& response );
		bool	handleProcessResponse(Response*& response, std::vector<char>& buffer);

		//		handleClientResponse
		bool	handleClientResponse(epoll_event& event);

		bool	handle_DELETE_requesition( void );

		// bool	responseClientListFiles( std::string pathDir, std::string pathFile );
		// bool	extractFileNameFromBody( aux_upload& data );




		std::string	generetePathErrorValid( int& status, const std::string& root, std::string path );
		bool		generetePathToResponse( std::string& dst , const std::string& root, const std::string& listNames );
		bool		responseClientError( int status, const std::string& root, std::string pathFileError );
		bool		findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint);

		bool	sendErrorToClient( std::string path, std::string header );

		bool	handleKeepAlive( void );
		bool	checkMethodSupported(std::vector<std::string> methods);
		bool	sendResponseClient( std::string response );
		void	timeoutHandler( void );
		bool	responseRedirect(std::string endPoint);
		bool	cleanupFd(int fd);
		void	cleanupResponse( int& fd );

		std::string	getErrorPageMapServer(std::string Error);
		std::string	getErrorPageMapLocation(const t_location*& _location, std::string Error);
		//				GETTERS to tests
		std::map<std::string, t_location*>	location( int port ) {
			return (this->_serversConf.at(port)->get_locations());
		}

		std::vector<Server_configuration*>	server( void ) {
			return (this->_parserFile->get_server_configuration());
		}

	private:
		Parser_configuration*	_parserFile;
		Parser_request*			_parserRequest;

		bool					_write;
		int						_client_fd;
		int						_epoll_fd;
		int						_port;

		std::string				**_verbs;
		// Response				**_response;

		std::map<int, Server_configuration*>	_serversConf;
		std::map<int, std::string>				_defaultErrorPage;
		std::map<int, Response*>				_responses;
		Server_configuration*					_serverUsing;
		std::time_t								_lastVerifyTimeout;
};

void		set_debug(bool	value);
int			get_debug( void );

bool		getContentFile(auxReadFiles& dst,  const std::map<std::string, std::string>& cgi, std::string statusHeader);
// void		generateDynamicHeader(auxReadFiles& tmp, std::string status_code);
void		generateHeaderDynamicStatus(auxReadFiles& tmp, std::string status);
bool		executeFork( ChildProcessData& infos);
// void		executeCGI(char** argv, char** envp);
// bool		getContentFile(auxReadFiles& dst);
void		appendBar(std::string& str);
bool		getContentFilePHP(auxReadFiles& dst);
// bool		generateFilesList(std::string& listFiles, const char* pathDir);
// bool		generateResponse(std::string& response);
std::string	generateHeaderRedirect(std::string status, std::string endPoint);
bool		readOuputFormatedCGI(ChildProcessData& auxProcess, std::string& oss);

std::string	get_stringError(int error);
