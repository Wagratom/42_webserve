/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientError.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/25 10:58:50 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendErrorToClient( std::string path, std::string statusHeader)
{
	auxReadFiles	tmp;

	write_debug_prefix("sendErrorToClient ", std::string(statusHeader + " To Client"));
	bzero(&tmp, sizeof(tmp));
	tmp.path = path;
	if (getContentFile(tmp, _serverUsing->get_cgi(), statusHeader) == false)
		return (false);
	return sendResponseClient(tmp.content);
}

std::string	Server::generetePathErrorValid(int& status, const std::string& root, std::string path)
{
	try {
		if (path.empty())
			path = _defaultErrorPage.at(status);
		else if (path[0] == '/')
		{
			path.erase(0, 1);
			path = root + path;
		}
		write_debug_prefix("generetePathErrorValid: path: ", path);
		return (path);
	} catch (const std::exception& e) {
		status = ERROR500;
		return (_defaultErrorPage.find(ERROR500)->second);
	}
}

bool	Server::responseClientError( int status, const std::string& root, std::string pathFileError)
{
	write_debug("responseClientError");
	pathFileError = generetePathErrorValid(status, root, pathFileError);
	if (status == ERROR400)
		return sendErrorToClient(pathFileError, "400 Bad Request");
	else if (status == ERROR403)
		return (sendErrorToClient(pathFileError, "403 Forbidden"));
	else if (status == ERROR404)
		return sendErrorToClient(pathFileError, "404 Not Found");
	else if (status == ERROR405)
		return sendErrorToClient(pathFileError, "405 Method Not Allowed");
	else if (status == ERROR413)
		return sendErrorToClient(pathFileError, "413 Payload Too Large");
	else if (status == ERROR500)
		return sendErrorToClient(pathFileError, "500 Internal Server Error");
	else if (status == ERROR504)
		return sendErrorToClient(pathFileError, "504 Gateway Timeout");
	// else if (status == ERROR415)
		// return (false);
	return (true);
}
