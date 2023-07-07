/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 09:23:29 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::checkClientMaxSize( int& contentLenght)
{
	std::string contentLength = getenv("CONTENT_LENGTH");
	contentLenght = std::strtol(contentLength.c_str(), NULL, 10);

	if (server()->get_clientMaxBodySize() > contentLenght)
		return true;

	char	buffer[4096];
	while (read(_client_fd, buffer, 4096) > 0);
	return write_error("checkClientMaxSize: content lenght too big");
}

bool	Server::handle_POST_requesition()
{
	int contentLenght = 0;

	std::cout << "handle_POST_requesition" << std::endl;
	if (checkClientMaxSize(contentLenght) == false)
		return (responseClientError(ERROR413, getErrorPageMapServer("413")));
	if (_parserRequest->get_request()[0])
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (redirectBodyCGI(contentLenght) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (responseServer("200"));
}
