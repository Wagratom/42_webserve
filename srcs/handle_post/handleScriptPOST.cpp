/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleScriptPOST.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/20 09:58:03 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::auxSendErrorPost( int status, std::string pathFileError )
{
	// char	buffer[4096];
	// while (read(_client_fd, buffer, 4096) > 0);
	responseClientError(status, _serverUsing->get_root() ,pathFileError);
	return (true);
}

bool	Server::createValidResponse( int& contentLength )
{
	write_debug("validatePostRequest");
	contentLength = std::strtol(getenv("CONTENT_LENGTH"), NULL, 10);
	if (_serverUsing->get_clientMaxBodySize() < contentLength)
		return (write_error("createValidResponse: contentLenght > clientMaxBodySize"));
	return true;
}

bool	Server::checkPermitionFile(std::string path)
{
	size_t	extension = path.find_last_of(".");

	write_debug_prefix("checkPermitionFile: ", path);
	if (extension == std::string::npos || extension == 0)
		auxSendErrorPost(ERROR404, getErrorPageMapServer("404"));
	if (access(path.c_str(), F_OK) == -1)
		auxSendErrorPost(ERROR404, getErrorPageMapServer("404"));
	else if (access(path.c_str(), W_OK) == -1)
		auxSendErrorPost(ERROR403, getErrorPageMapServer("403"));
	else
		return (true);
	return write_error("handlePostRequest: Not Access path: " + path);
}

bool	Server::handleScriptPOST( void )
{
	int	contentLenght;

	write_debug("handleScriptPOST");
	if (checkPermitionFile(getenv("SCRIPT_FILENAME")) == false)
		return (true);
	if (_parserRequest->get_request()[0])
		return (auxSendErrorPost(ERROR400, getErrorPageMapServer("400")));
	if (createValidResponse(contentLenght) == false)
		return (auxSendErrorPost(ERROR413, getErrorPageMapServer("413")));
	if (createNewResponses(contentLenght) == false)
		return (auxSendErrorPost(ERROR500, getErrorPageMapServer("500")));
	if (handlePostBody() == false)
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500")));
	return (true);

}
