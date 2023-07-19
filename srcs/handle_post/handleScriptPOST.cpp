/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleScriptPOST.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/18 19:22:01 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::auxSendErrorPost( int status, std::string pathFileError )
{
	char	buffer[4096];
	while (read(_client_fd, buffer, 4096) > 0);
	responseClientError(status, _serverUsing->get_root() ,pathFileError);
	return handleKeepAlive();
}

bool	Server::createValidResponse( void )
{
	std::string	contentLength = getenv("CONTENT_LENGTH");
	int			contentLengthInt;

	write_debug("validatePostRequest");
	contentLengthInt = std::strtol(contentLength.c_str(), NULL, 10);
	if (_serversConf[_port]->get_clientMaxBodySize() < contentLengthInt)
		return (write_error("createValidResponse: contentLenght > clientMaxBodySize"));
	if (_responses.find(_client_fd) != _responses.end())
		return true;
	try {
		_responses.insert(std::pair<int, Response*>(_client_fd, new Response));
		_responses.at(_client_fd)->contentLenght = contentLengthInt;
		_responses.at(_client_fd)->write = _write;
		return true;
	}
	catch (std::exception& e) {
		write_error("createValidResponse: " + std::string(e.what()));
		return false;
	}
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
	write_debug("handleScriptPOST");
	if (checkPermitionFile(getenv("SCRIPT_FILENAME")) == false)
		return (true);
	if (_parserRequest->get_request()[0])
		return (auxSendErrorPost(ERROR400, getErrorPageMapServer("400")));
	if (createValidResponse() == false)
		return (auxSendErrorPost(ERROR413, getErrorPageMapServer("413")));
	if (handlePostBody() == false)
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500")));
	return (true);

}
