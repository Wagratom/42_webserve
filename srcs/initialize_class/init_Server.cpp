/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:01:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/13 09:26:47 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::initializeDefaultErrorPage( void )
{
	_defaultErrorPage[ERROR400] = "./error_pages/400_bad_request.html";
	_defaultErrorPage[ERROR404] = "./error_pages/404_lufyPensativo.html";
	_defaultErrorPage[ERROR413] = "./error_pages/413_payload_too_large.html";
	_defaultErrorPage[ERROR500] = "./error_pages/500_internal_server.html";
	// _defaultErrorPage[ERROR415] = "./error_pages/415_unsupported_media.html";
}

std::string**	Server::create_verbs( void )
{
	std::string** verbs = new std::string*[4];
	verbs[0] = new std::string("GET");
	verbs[1] = new std::string("POST");
	verbs[2] = new std::string("DELETE");
	verbs[3] = NULL;
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
			, _pathIndexServer("")
			, _verbs(create_verbs())
{
	_response = new Response*[1024];
	memset(_response, 0, sizeof(Response*) * 1024);
	// initializeResponses();
	initializeDefaultErrorPage();
};

Server::~Server() {
	delete	_parserFile;
	// if (_parserRequest)
		// delete _parserRequest;
	for (size_t i = 0; _verbs[i] != NULL; i++) {
		delete _verbs[i];
	}
	delete [] _verbs;
	for (size_t i = 0; i < 1024; i++) {
		if (_response[i])
			delete _response[i];
	}
	delete [] _response;
};
