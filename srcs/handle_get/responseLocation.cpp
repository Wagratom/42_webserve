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

static bool	hasRedirection(const t_location* location)
{
	return (location->configuration->get_return().empty() == false);
}

static bool	isRequerimentFile(std::string& endPoint)
{
	return (endPoint.find(".") != std::string::npos);
}

static bool	isEndPoint(std::string endPoint, std::string& locationName)
{
	if (endPoint[endPoint.length() - 1] != '/')
		endPoint += "/";
	if (endPoint == locationName)
		return (true);
	return (false);
}

bool	Server::createRootLocation(const t_location* location)
{
	if (location->configuration->get_root().empty() == false)
		return (true);
	std::string	rootServer = _serversConf[_port]->get_root();
	if (rootServer.empty())
		write_error("Error: root not found");
	location->configuration->set_root(rootServer);
	return (true);
}

bool	Server::responseLocation(std::string endPoint, std::string locationName)
{
	t_location*							_location = location(_port).at(locationName);

	write_debug("responseLocation");
	if (_location == NULL)
		return (responseClientError(ERROR500, _serversConf[_port]->get_root(), getErrorPageMapLocation(_location, "500")));
	if (hasRedirection(_location))
		return (responseRedirect(_location->configuration->get_return()));
	if (isRequerimentFile(endPoint))
		return (responseFileLocation(_location, endPoint));
	if (isEndPoint(endPoint, locationName))
		return (returnIndexLocation(_location));
	return (responseClientError(ERROR404, _serversConf[_port]->get_root(), getErrorPageMapLocation(_location, "404")));
}

bool	Server::returnIndexLocation(t_location* location)
{
	auxReadFiles	tmp;

	write_debug("returnIndexLocation");
	if (createRootLocation(location) == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "500")));
	if (generetePathToResponse(tmp.path, location->configuration->get_root(), location->configuration->get_index()) == false)
		return (responseAutoIndexOrErrorLocation(location));
	if (getContentFile(tmp, location->configuration->get_cgi()) == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "500")));
	// generateDynamicHeader(tmp, "200");
	// tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.content));
}

static void	set_PathAutoindex( t_location* location)
{
	// std::string endPoint = location->endPoint;

	// if (endPoint[0] == '/')
		// endPoint.erase(0, 1);
	// std::string path = location->configuration->get_root() + endPoint;
	// write_debug_prefix("setPathAutoindex: ", path);
	setenv("PATHDIR", location->configuration->get_root().c_str(), 1);
}

bool	Server::responseAutoIndexOrErrorLocation( t_location* location )
{
	auxReadFiles	tmp;

	write_debug("responseAutoIndexOrErrorLocation");
	if (location->configuration->get_autoIndex() == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "404")));
	tmp.path = AUTO_INDEX;
	set_PathAutoindex(location);
	if (getContentFile(tmp, location->configuration->get_cgi()) == false)
		return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMapLocation(location, "500")));
	return (sendResponseClient(tmp.content));
}
