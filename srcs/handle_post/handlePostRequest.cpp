/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 13:01:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::validatePostRequest( void )
{
	std::string	contentLength = getenv("CONTENT_LENGTH");
	Response*	response = _response[_client_fd];

	std::cout << "validatePostRequest" << std::endl;
	response->contentLenght = std::strtol(contentLength.c_str(), NULL, 10);
	if (_parserRequest->get_request()[0])
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (server()->get_clientMaxBodySize() < response->contentLenght)
	{
		char	buffer[4096];
		while (read(_client_fd, buffer, 4096) > 0);
		return (responseClientError(ERROR413, getErrorPageMapServer("413")));
	}
	response->content.resize(response->contentLenght);
	return true;
}

bool	Server::handleBodyPost( void )
{
	Response*	response = _response[_client_fd];
	char*		initialPos = (response->content.data() + response->BytesRead);
	int			rest = response->contentLenght - response->BytesRead;

	std::cout << "handleBodyPost" << std::endl;
	response->BytesRead += read(_client_fd, initialPos, rest);
	if (response->BytesRead < 0)
		return (write_error(strerror(errno)));
	std::cout << "Bytes read: " << response->BytesRead << std::endl;
	if (response->BytesRead < response->contentLenght)
		return (true);
	if (redirectBodyCGI() == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (responseServer("200"));
}

bool	Server::handlePostRequest()
{
	std::cout << "handlePostRequest" << std::endl;
	if (_response[_client_fd] == NULL)
	{
		_response[_client_fd] = new Response;
		if (validatePostRequest() == false)
			return false;
	}
	return (handleBodyPost());
}
