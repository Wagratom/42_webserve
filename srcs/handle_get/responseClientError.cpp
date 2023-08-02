/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientError.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/01 22:50:03 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendErrorToClient( std::string path, std::string statusHeader)
{
	auxReadFiles	tmp;

	write_debug_prefix("sendErrorToClient ", std::string(statusHeader + " To Client"));
	bzero(&tmp, sizeof(tmp));
	tmp.path = path;
	if (getContentFile(tmp, _response->cgi, statusHeader) == false)
		return (false);
	sendResponseClient(tmp.content);
	return cleanupClient(_client_fd);
}

bool	Server::genereteValidpath(std::string& path)
{
	write_debug("genereteValidpath");
	try{
		std::string	extension = path.substr(path.find_last_of("."));

		if (access(path.c_str(), F_OK) == -1)
		{
			path = _defaultErrorPage[ERROR404];
			return write_error_prefixS("Path error not found: Response client with page default: ", path);
		}
		if (_response->cgi.find(extension) != _response->cgi.end())
		{
			if (access(path.c_str(), X_OK) == -1)
			{
				path = _defaultErrorPage[ERROR403];
				return write_error_prefixS("Path not permition: Response client with page default: ", path);
			}
		}
		else if (access(path.c_str(), R_OK) == -1)
		{
			path = _defaultErrorPage[ERROR403];
			return write_error_prefixS("Path not permition: Response client with page default: ", path);
		}
		return (true);
	}
	catch (const std::exception& e) {
		path = _defaultErrorPage[ERROR500];
		return write_error_prefixS("genereteValidpath: ", e.what());
	}
}

bool	Server::responseClientError(int status, const std::string& root, std::string path)
{
	write_debug("responseClientError");
	path = root + path;
	genereteValidpath(path);
	if (status == ERROR400)
		return sendErrorToClient(path, "400 Bad Request");
	else if (status == ERROR403)
		return (sendErrorToClient(path, "403 Forbidden"));
	else if (status == ERROR404)
		return sendErrorToClient(path, "404 Not Found");
	else if (status == ERROR405)
		return sendErrorToClient(path, "405 Method Not Allowed");
	else if (status == ERROR413)
		return sendErrorToClient(path, "413 Payload Too Large");
	else if (status == ERROR500)
		return sendErrorToClient(path, "500 Internal Server Error");
	else if (status == ERROR504)
		return sendErrorToClient(path, "504 Gateway Timeout");
	return (true);
}
