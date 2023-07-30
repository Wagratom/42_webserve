/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseFileServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/24 17:45:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	isPostMethod( void )
{
	if (std::string(getenv("REQUEST_METHOD")) == "POST")
		return (true);
	return (false);
}

bool	Server::preparingToReadFile(auxReadFiles& tmp, std::string& endPoint)
{
	size_t			checkExtensionFile = endPoint.find_last_of('.');

	if (checkExtensionFile == std::string::npos || checkExtensionFile == 0)
		return write_error("preparingToReadFile: not found extension file");
	endPoint.erase(0, 1);
	tmp.path = _serverUsing->get_root() + endPoint;
	return true;
}

bool Server::responseFileServer(std::string& endPoint)
{
	auxReadFiles	tmp;

	bzero(&tmp, sizeof(tmp));
	write_debug("responseFileServer");
	_response->errorMap = _serverUsing->get_error_page();
	if (preparingToReadFile(tmp, endPoint) == false)
		return (responseClientError(ERROR404, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "404")));
	return responseClient(tmp, _serverUsing->get_cgi(), "200 OK");
}

bool	Server::responseFileLocation(const t_location*& location, std::string& endPoint)
{
	auxReadFiles	tmp;

	bzero(&tmp, sizeof(tmp));
	write_debug("responseFileLocation");
	endPoint.erase(0, location->endPoint.length());
	tmp.path = location->configuration->get_root() + endPoint;
	if (isPostMethod())
	{
		setenv("SCRIPT_FILENAME", tmp.path.c_str(), 1);
		return handleScriptPOST();
	}
	return responseClient(tmp, location->configuration->get_cgi(), "200 OK");
}
