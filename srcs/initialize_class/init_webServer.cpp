/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_webServer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:01:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/09/07 13:13:17 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::initializeDefaultErrorPage( void )
{
	_defaultErrorPage["400"] = "./root/error_pages/400_bad_request.html";
	_defaultErrorPage["404"] = "./root/error_pages/404_lufyPensativo.html";
	_defaultErrorPage["403"] = "./root/error_pages/403_forbidden.html";
	_defaultErrorPage["405"] = "./root/error_pages/405_method_not_allowed.html";
	_defaultErrorPage["413"] = "./root/error_pages/413_payload_too_large.html";
	_defaultErrorPage["500"] = "./root/error_pages/500_internal_server.html";
	_defaultErrorPage["504"] = "./root/error_pages/504_gateway_timeout.html";

}

std::string**	Server::create_verbs( void )
{
	std::string** verbs = new std::string*[10];
	verbs[0] = new std::string("GET");
	verbs[1] = new std::string("POST");
	verbs[2] = new std::string("DELETE");
	verbs[3] = new std::string("HEAD");
	verbs[4] = new std::string("PUT");
	verbs[5] = new std::string("CONNECT");
	verbs[6] = new std::string("OPTIONS");
	verbs[7] = new std::string("TRACE");
	verbs[8] = new std::string("PATCH");
	verbs[9] = NULL;
	return (verbs);
}

// void	Server::initializeResponses( void )
// {
// 	for (int i = 0; i < 1024; i++)
// 	{
// 		_response[i] = new Response;
// 		_response[i]->contentLenght = 0;
// 		_response[i]->BytesRead = 0;
// 	}
// }

Server::Server(std::string filename)
			: _parserFile(new Parser_configuration(filename))
			, _parserRequest(NULL)
			, _write(false)
			, _client_fd(-1)
			, _epoll_fd(-1)
			, _port(0)
			, _verbs(create_verbs())
{
	// initializeResponses();
	initializeDefaultErrorPage();
};

Server::~Server() {
	delete	_parserFile;
	for (size_t i = 0; _verbs[i] != NULL; i++) {
		delete _verbs[i];
	}
	delete [] _verbs;
	// for (std::map<int, Response*>::iterator it = _responses.begin(); it != _responses.end(); it++) {
		// delete it->second;
	// }
	for (std::map<int, Response*>::iterator it = _responses.begin(); it != _responses.end(); it++) {
		delete it->second;
	}
};



/*								RESPONSE									  */

Response::Response( void )
	: contentLenght(0)
	, bytesRead(0)
	, sizeContent(0)
	, port(0)
	, clientMaxBodySize(0)
	, hasProcess(false)
	, write(false)
	, isProcessAutoindex(false)
	, endHeader(false)
	, creationTime(std::time(NULL))
	, buffer("")
	, method("")
	, root("")
	, index("")
	, cgi()
	, locations()
	, errorPage() {
	bzero(&process, sizeof(ChildProcessData));
};
