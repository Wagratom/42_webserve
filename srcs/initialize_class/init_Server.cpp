/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:01:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/16 16:43:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::initializeDefaultErrorPage( void )
{
	_defaultErrorPage[ERROR400] = "./error_pages/400_bad_request.html";
	_defaultErrorPage[ERROR404] = "./error_pages/404_lufyPensativo.html";
	_defaultErrorPage[ERROR403] = "./error_pages/403_forbidden.html";
	_defaultErrorPage[ERROR405] = "./error_pages/405_method_not_allowed.html";
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
