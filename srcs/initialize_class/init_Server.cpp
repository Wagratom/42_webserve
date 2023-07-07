/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:01:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 11:45:05 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::initializeDefaultErrorPage( void )
{
	_defaultErrorPage[ERROR404] = "./error_pages/404_lufy_pensativo.html";
	_defaultErrorPage[ERROR400] = "./error_pages/400_bad_request.html";
	_defaultErrorPage[ERROR415] = "./error_pages/415_unsupported_media.html";
	_defaultErrorPage[ERROR500] = "./error_pages/500_internal_server.html";
	_defaultErrorPage[ERROR413] = "./error_pages/413_payload_too_large.html";
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
			, _server_fd(-1)
			, _client_fd(-1)
			, _epoll_fd(-1)
			, _number_of_events(-1)
			, _write(false)
			, _response(new Response*[1024])
			, _verbs(create_verbs())
{
	// initializeResponses();
	initializeDefaultErrorPage();
};

Server::~Server() {
	if (_parserRequest)
		delete _parserRequest;
	delete	_parserFile;
	for (int i = 0; i < 10; i++) {
		delete _verbs[i];
	}
	delete [] _verbs;
	delete [] _response;
};
