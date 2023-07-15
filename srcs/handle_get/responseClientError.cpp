/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientError.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/15 10:12:44 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendErrorToClient( std::string path, std::string error)
{
	auxReadFiles	tmp;
	std::string		header;

	write_debug_prefix("sendError ", std::string(error + " To Client"));
	tmp.path = path;
	if (getContentFile(tmp) == false)
		return (false);
	return sendResponseClient(tmp.content);
}

std::string	Server::generetePathErrorValid(int status, std::string root, std::string path)
{
	if (path.empty())
		return (_defaultErrorPage.find(status)->second);
	if (path[0] == '.')
		return (path);
	if (path[0] == '/')
	{
		path.erase(0, 1);
		return (root + path);
	}
	return (root + path);
}

bool	Server::responseClientError( int status, std::string root, std::string pathFileError)
{
	write_debug("responseClientError");
	pathFileError = generetePathErrorValid(status, root, pathFileError);
	if (status == ERROR404)
		return sendErrorToClient(pathFileError, "404 Not Found");
	else if (status == ERROR500)
		return sendErrorToClient(pathFileError, "500 Internal Server Error");
	else if (status == ERROR400)
		return sendErrorToClient("./error_pages/400_bad_request.html", "400 Bad Request");
	else if (status == ERROR415)
		// enviar um error de formato do payload não é um formato suportado.
		return (false);
	else if (status == ERROR413)
		return sendErrorToClient(pathFileError, "413 Payload Too Large");
	return (true);
}
