/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/11 23:35:58 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::validatePostRequest( void )
{
	std::string	contentLength = getenv("CONTENT_LENGTH");
	Response*	response = _response[_client_fd];

	write_debug("validatePostRequest");
	response->contentLenght = std::strtol(contentLength.c_str(), NULL, 10);
	if (_parserRequest->get_request()[0])
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (_serversConf[_port]->get_clientMaxBodySize() < response->contentLenght)
	{
		char	buffer[4096];
		while (read(_client_fd, buffer, 4096) > 0);
		return (false);
	}
	return true;
}

bool	Server::handlePostRequest()
{
	std::cout << "\nhandlePostRequest" << std::endl;
	if (_response[_client_fd] == NULL)
	{
		_response[_client_fd] = new Response;
		if (validatePostRequest() == false)
			return (responseClientError(ERROR413, getErrorPageMapServer("413")));
	}
	if (handlePostBody() == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	if (_response[_client_fd]->endProcess)
		return (responseServer("200"));
	return (true);

}
