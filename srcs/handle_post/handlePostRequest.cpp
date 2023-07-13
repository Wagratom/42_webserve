/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/13 13:49:47 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createValidResponse( void )
{
	std::string	contentLength = getenv("CONTENT_LENGTH");
	int			contentLengthInt;

	write_debug("validatePostRequest");
	contentLengthInt = std::strtol(contentLength.c_str(), NULL, 10);
	if (_serversConf[_port]->get_clientMaxBodySize() < contentLengthInt)
		return (write_error("createValidResponse: contentLenght > clientMaxBodySize"));
	_responses.find(_client_fd)->second = new Response;
	_responses.find(_client_fd)->second->contentLenght = contentLengthInt;
	_responses.find(_client_fd)->second->write = _write;
	return true;
}

bool	Server::auxSendErrorPost( int status, std::string pathFileError )
{
	char	buffer[4096];
	while (read(_client_fd, buffer, 4096) > 0);
	responseClientError(status, pathFileError);
	return handleKeepAlive();
}

bool	Server::handlePostRequest()
{

	write_debug("handlePostRequest");
	if (_parserRequest->get_request()[0])
		return (auxSendErrorPost(ERROR400, getErrorPageMapServer("400")));
	if (createValidResponse() == false)
		return (auxSendErrorPost(ERROR413, getErrorPageMapServer("413")));
	if (handlePostBody() == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (true);

}
