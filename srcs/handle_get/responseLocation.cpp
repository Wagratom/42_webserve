/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseLocation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	hasRedirection(const t_location*& location)
{
	return (location->configuration->get_return().empty() == false);
}

static bool	isRequerimentFile(const std::string& endPoint)
{
	return (endPoint.find(".") != std::string::npos);
}

static bool	isEndPoint(std::string& endPoint, std::string& locationName)
{
	if (endPoint[endPoint.length() - 1] != '/')
		endPoint += "/";
	if (endPoint == locationName)
		return (true);
	return (false);
}

bool	Server::createRootLocation(const t_location*& location)
{
	if (location->configuration->get_root().empty() == false)
		return (true);
	std::string	rootServer = _serversConf[_port]->get_root();
	if (rootServer.empty())
		write_error("Error: root not found");
	location->configuration->set_root(rootServer);
	return (true);
}

bool	Server::responseLocation(std::string& endPoint, std::string& locationName)
{
	const t_location*&	_location = (const t_location*&)location(_port).at(locationName);

	write_debug("responseLocation");
	if (_location == NULL)
		return (responseClientError(ERROR500, _serversConf[_port]->get_root(), getErrorPageMapLocation(_location, "500")));
	if (checkMethodSupported(_location->configuration->get_limit_except()) == false)
		return (responseClientError(ERROR405, _serversConf[_port]->get_root(), getErrorPageMapLocation(_location, "405")));
	if (hasRedirection(_location))
		return (responseRedirect(_location->configuration->get_return()));
	if (isRequerimentFile(endPoint))
		return (responseFileLocation(_location, endPoint));
	if (isEndPoint(endPoint, locationName))
		return (returnIndexLocation(_location));
	return (responseClientError(ERROR404, _serversConf[_port]->get_root(), getErrorPageMapLocation(_location, "404")));
}

bool	Server::returnIndexLocation(const t_location*& location)
{
	auxReadFiles	tmp;
	// Location_configuration* locationConf = location->configuration;

	write_debug("returnIndexLocation");
	if (createRootLocation(location) == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "500")));
	if (generetePathToResponse(tmp.path, location->configuration->get_root(), location->configuration->get_index()) == false)
		return (get_autoindex(location->configuration->get_autoIndex(), location->configuration->get_root()));
	if (getContentFile(tmp, location->configuration->get_cgi(), "200 OK") == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "500")));
	// generateDynamicHeader(tmp, "200");
	// tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.content));
}
