/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/09/18 12:05:42 by wwallas-         ###   ########.fr       */
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

# define ERROR400 "400" // Bad Request
# define ERROR403 "403" // Forbidden
# define ERROR404 "404" // Not Found
# define ERROR405 "405" // Method Not Allowed
# define ERROR413 "413" // Payload Too Large
# define ERROR415 "415" // Unsupported Media Type
# define ERROR500 "500" // Internal Server Error
# define ERROR504 "504" // Gateway Timeout

# define CHILD_PROCESS 0

# define PATH_CGI "/usr/bin/php-cgi"
# define PATH_UPLOAD "/uploads/"
# define AUTO_INDEX "./autoindex.php"

#define MAX_SIZE_HEADER 1000000

class	Response
{
	public:
		Response( void );

	public:
		int						contentLenght;
		int						bytesRead;
		int						sizeContent;
		int						port;
		int						clientMaxBodySize;
		bool					hasProcess;
		bool					write;
		bool					isProcessAutoindex;
		bool					endHeader;
		bool					autoindex;
		std::time_t				creationTime;
		std::string				buffer;
		std::string				method;
		std::string				root;
		std::string				index;
		ChildProcessData		process;
		std::map<std::string, std::string>	cgi;
		std::map<std::string, t_location*>	locations;
		std::map<std::string, std::string*>	errorPage;
};

class	Server
{
	public:
		Server(std::string filename);
		~Server( void );

		std::string**	create_verbs( void );
		void			initializeDefaultErrorPage( void );

		bool	initializeServer( void );

		bool	createServerConfigured( void );
		bool	create_epoll( void );
		bool	createServer( int& serverFd, Server_configuration* server );
		bool	createSockeConfigured( int& serverFd );
		bool	bind_socket( int& serverFd, Server_configuration* server );
		bool	listen_socket( int& serverFd );
		bool	add_mode_read( int& serverFD );

		int		startServer( void );
		bool	captureNewEvents( epoll_event* event, int& numberOfEvents );
		bool	filterEvent( epoll_event* event, int numberOfEvents );

		bool	handleNewConnections( int serverFd ); // if
		bool	accept_status( int& new_client, int& serverFD );
		bool	save_connection( int& new_client );

		bool	handleEvents( epoll_event& event ); // else
		bool	isClosedOrErrorEvent( epoll_event& event );
		bool	savaDataCleint( epoll_event& event );
		bool	configureEnvsServer(epoll_event& event);
		bool	createNewResponses( void );

		bool	handleRequestClient( void ); // leitura
		bool	readHeaderRequest( void );
		bool	responseRequest( void );

		bool	handle_GET_requesition( void ); // GET
		void	handleQuerystring(std::string& endPoint);
		bool	responseServer( void );
		bool	responseFileServer( std::string endPoint );
		bool	responseLocation( std::string endPoint, std::string& locationName );
		bool	handle_request_location(const t_location*& location, std::string& path);
		void	updateResponseLocation(const t_location*& location, bool& is_location_server);
		bool	returnIndexLocation( void );
		bool	responseFileLocation(const t_location*& location, std::string& endPoint);

		bool	handlePostRequest( void ); // POST
		bool	handleScriptPOST( void );
		bool	checkPermitionFile( void );
		bool	checkClientMaxSize( void );
		bool	handlePostBody( void );
		bool	readAndSaveDatas( void );
		bool	createProcessResponse( void );
		void	handleProcessPOST( void );
		bool	handleProcessResponse( void );

		bool	handle_DELETE_requesition( void ); // DELETE

		//		handleClientResponse
		bool	handleClientResponse( void ); // escrita
		bool	handleProcessClient( void );

		// bool	auxSendErrorPost( int status, std::string Error );
		bool	preparingToReadFile(auxReadFiles& tmp, std::string& endPoint);
		bool	createRootLocation(const t_location*& location, bool& is_location_server);
		bool	sendAutoindex( const bool& autoindex, const std::string& root);

		bool	generetePathToResponse( std::string& dst , const std::string& root, const std::string& listNames );
		bool	responseClientError( std::string error, std::string pathFileError );
		bool	genereteValidpath( std::string& path );
		bool	findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint);

		bool	sendErrorToClient( std::string path, std::string header );

		bool	handleKeepAlive( void );
		bool	checkMethodSupported(std::vector<std::string> methods);
		bool	sendResponseClient( std::string response );
		bool	timeoutHandler( void );
		bool	responseRedirect(std::string endPoint);
		bool	cleanupFd(int fd);
		bool	cleanupClient(int& fd);
		void	cleanupResponse( int& fd );

		bool	getContentFile(auxReadFiles& dst, const std::map<std::string, std::string>& cgi, std::string statusHeader);
		bool	responseClient(auxReadFiles& dst, const std::map<std::string, std::string>& cgi, std::string statusHeader);
		bool	getContentFilePHP(auxReadFiles& dst);

		std::string	getErrorPageMap( std::string Error );
		//				GETTERS to tests
		std::map<std::string, t_location*>	location( int port ) {
			return (this->_serversConf.at(port)->get_locations());
		}

		std::vector<Server_configuration*>	server( void ) {
			return (this->_parserFile->get_server_configuration());
		}

		bool	is_get_server( void );
		bool	seed_head_client( void );

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
		std::map<std::string, std::string>		_defaultErrorPage;
		std::map<int, Response*>				_responses;
		std::time_t								_lastVerifyTimeout;
		Response*								_response;
};

void		set_debug(bool	value);
int			get_debug( void );

bool		getContentFile(auxReadFiles& dst,  const std::map<std::string, std::string>& cgi, std::string statusHeader);
// void		generateDynamicHeader(auxReadFiles& tmp, std::string status_code);
void		generateHeaderDynamicStatus(auxReadFiles& tmp, std::string status);
bool		executeFork( ChildProcessData& infos);
std::string	generateHeaderRedirect(std::string status, std::string endPoint);
bool		readOuputFormatedCGI(std::string& dst, const ChildProcessData& auxProcess);

std::string	get_stringError(int error);
