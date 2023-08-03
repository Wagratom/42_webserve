/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleScriptPOST.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/03 10:48:17 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

// bool	Server::responseClientError( int status, std::string pathFileError )
// {
// 	// char	buffer[4096];
// 	// while (read(_client_fd, buffer, 4096) > 0);
// 	responseClientError(status, _response->root ,pathFileError);
// 	return (true);
// }

bool	Server::checkClientMaxSize( void )
{
	write_debug("checkClientMaxBodySize");
	_response->contentLenght = std::strtol(getenv("CONTENT_LENGTH"), NULL, 10);
	if (_response->clientMaxBodySize < _response->contentLenght)
		return (write_error("createValidResponse: contentLenght > clientMaxBodySize"));
	return true;
}

bool	Server::checkPermitionFile()
{
	try {
		std::string	path = getenv("SCRIPT_FILENAME");
		size_t	extension = path.find_last_of(".");
		write_debug_prefix("checkPermitionFile: ", path);
		if (extension == std::string::npos || extension == 0)
			responseClientError("404", getErrorPageMap("404"));
		else if (access(path.c_str(), F_OK) != 0)
			responseClientError("404", getErrorPageMap("404"));
		else if (access(path.c_str(), X_OK) != 0)
			responseClientError("403", getErrorPageMap("403"));
		else if (access(path.c_str(), R_OK) != 0)
			responseClientError("403", getErrorPageMap("403"));
		else
			return (true);
		cleanupFd(_client_fd);
		return (false);
	}
	catch (const std::exception& e) {
		responseClientError("500", getErrorPageMap("500"));
		return (write_error("checkPermitionFile: " + std::string(e.what())));
	}

}

bool	Server::handleScriptPOST( void )
{
	write_debug("handleScriptPOST");
	if (checkPermitionFile() == false)
		return (true);
	if (checkClientMaxSize() == false)
		return (responseClientError("413", getErrorPageMap("413")));
	_response->sizeContent = _response->buffer.size();
	_response->bytesRead = _response->sizeContent;
	if (handlePostBody() == false)
		return (responseClientError("500", getErrorPageMap("500")));
	return (true);

}
