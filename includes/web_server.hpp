/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web_server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:40:58 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/01 20:01:38 by wwallas-         ###   ########.fr       */
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
		Response( void );

	public:
		int						contentLenght;
		int						bytesRead;
		int						sizeContent;
		int						port;
		bool					hasProcess;
		bool					write;
		bool					isProcessAutoindex;
		bool					endHeader;
		std::time_t				creationTime;
		std::string				buffer;
		std::string				method;
		ChildProcessData		process;
		std::map<std::string, std::string*>	errorMap;
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
		bool	responseFileServer( std::string& endPoint );
		bool	responseLocation( std::string& endPoint, std::string& locationName );
		bool	returnIndexLocation(const t_location*& _location );
		bool	responseFileLocation(const t_location*& location, std::string& endPoint);

		bool	handlePostRequest( void ); // POST
		bool	handleScriptPOST( void );
		bool	checkPermitionFile(std::string path);
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

		bool	auxSendErrorPost( int status, std::string Error );
		bool	preparingToReadFile(auxReadFiles& tmp, std::string& endPoint);
		bool	createRootLocation(const t_location*& location);
		bool	sendAutoindex( const bool& autoindex, const std::string& root);

		bool		generetePathToResponse( std::string& dst , const std::string& root, const std::string& listNames );
		bool		responseClientError( int status, const std::string& root, std::string pathFileError );
		bool		findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint);

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

		std::string	getErrorPageMap(const std::map<std::string, std::string*>& errorMap, std::string Error);
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
		Response*								_response;
};

void		set_debug(bool	value);
int			get_debug( void );

bool		getContentFile(auxReadFiles& dst,  const std::map<std::string, std::string>& cgi, std::string statusHeader);
// void		generateDynamicHeader(auxReadFiles& tmp, std::string status_code);
void		generateHeaderDynamicStatus(auxReadFiles& tmp, std::string status);
bool		executeFork( ChildProcessData& infos);
// void		executeCGI(char** argv, char** envp);
// bool		getContentFile(auxReadFiles& dst);
// void		appendBar(std::string& str);
// bool		generateFilesList(std::string& listFiles, const char* pathDir);
// bool		generateResponse(std::string& response);
std::string	generateHeaderRedirect(std::string status, std::string endPoint);
bool		readOuputFormatedCGI(std::string& dst, const ChildProcessData& auxProcess);

std::string	get_stringError(int error);
