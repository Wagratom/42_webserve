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

bool Server::responseFileServer(std::string endPoint)
{
	auxReadFiles	tmp;

	std::cout << "responseFileServer" << std::endl;
	endPoint.erase(0, 1);
	tmp.path = _serversConf[_port]->get_root() + endPoint;
	if (endPoint.find(".") == std::string::npos)
		return (responseClientError(ERROR404, getErrorPageMapServer("404")));
	if (getContentFile(tmp) == false)
		return (responseClientError(ERROR404, getErrorPageMapServer("404")));
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	if (sendResponseClient(tmp.response) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return true;
}

bool	Server::responseFileLocation(t_location* location, std::string endPoint)
{
	auxReadFiles	tmp;

	endPoint.erase(0, location->endPoint.length());
	tmp.path = location->configuration->get_root() + endPoint;
	if (getContentFile(tmp) == false)
		return (responseClientError(ERROR404, getErrorPageMapLocation(location, "404")));
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	if (sendResponseClient(tmp.response) == false)
		return (responseClientError(ERROR500, getErrorPageMapLocation(location, "500")));
	return true;
}
