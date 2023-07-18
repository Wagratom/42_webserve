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

	write_debug("responseFileServer");
	if (preparingToReadFile(tmp, endPoint) == false)
		return (responseClientError(ERROR404, _serverUsing->get_root(), getErrorPageMapServer("404")));
	if (getContentFile(tmp, _serverUsing->get_cgi(), "200 OK") == false)
	{
		if (tmp.notPermmision == true)
			return (responseClientError(ERROR403, _serverUsing->get_root(), getErrorPageMapServer("403")));
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500")));
	}
	if (sendResponseClient(tmp.content) == false)
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500")));
	return true;
}

bool	Server::responseFileLocation(const t_location*& location, std::string& endPoint)
{
	auxReadFiles	tmp;

	write_debug("responseFileLocation");
	endPoint.erase(0, location->endPoint.length());
	tmp.path = location->configuration->get_root() + endPoint;
	if (getContentFile(tmp, location->configuration->get_cgi(), "200 OK") == false)
		return (responseClientError(ERROR404, location->configuration->get_root(), getErrorPageMapLocation(location, "404")));
	if (sendResponseClient(tmp.content) == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "500")));
	return true;
}
