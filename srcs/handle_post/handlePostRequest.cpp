/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 11:00:37 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createValidResponse( void )
{
	_response[_client_fd] = new Response;
	Response* response = _response[_client_fd];
	std::string	contentLength = getenv("CONTENT_LENGTH");

	write_debug("validatePostRequest");
	response->contentLenght = std::strtol(contentLength.c_str(), NULL, 10);
	if (_serversConf[_port]->get_clientMaxBodySize() < response->contentLenght)
		return (false);
	return true;
}

bool	Server::auxSendErrorPost( int status, std::string pathFileError )
{
	char	buffer[4096];
	while (read(_client_fd, buffer, 4096) > 0);
	return (responseClientError(status, pathFileError));
}

bool	Server::handlePostRequest()
{
	std::cout << "\nhandlePostRequest" << std::endl;

	if (_parserRequest->get_request()[0])
		return (auxSendErrorPost(ERROR400, getErrorPageMapServer("400")));
	if (createValidResponse() == false)
		return (auxSendErrorPost(ERROR413, getErrorPageMapServer("413")));
	if (handlePostBody() == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (true);

}
