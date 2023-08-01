/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientError.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/01 20:17:29 by wwallas-         ###   ########.fr       */
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


bool	Server::responseClientError( int status, const std::string& root, std::string pathFileError)
{
	write_debug("responseClientError");
	pathFileError = root + pathFileError;
	if (access(pathFileError.c_str(), R_OK) != 0)
	{
		pathFileError = _defaultErrorPage[status];
		write_error_prefixS("Path error not found: Response client with page default: ", pathFileError);
	}
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
	return (true);
}
