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

static bool	isPostMethod( void )
{
	if (std::string(getenv("REQUEST_METHOD")) == "POST")
		return (true);
	return (false);
}

static bool	isValidLocation(std::string location, std::string name)
{
	if (location[0] == '/')
		location.erase(0,1);
	if (location != name)
		return false;
	return true;
}

bool	Server::createRootLocation(const t_location*& location)
{
	if (location->configuration->get_root().empty() == false)
		return (true);
	std::string	rootServer = _response->root;
	if (rootServer.empty())
		write_error("Error: root not found");
	location->configuration->set_root(rootServer);
	return (true);
}

bool	Server::checkMethodSupported(std::vector<std::string> methods)
{
	std::string	method = getenv("REQUEST_METHOD");

	if (methods.empty())
		return (true);
	for (size_t i = 0; i < methods.size(); i++)
	{
		if (methods[i] == method)
			return (true);
	}
	write_error("Error: method not supported");
	return (false);
}

void	Server::updateResponseLocation(const t_location*& location)
{
	_response->errorPage = location->configuration->get_error_page();
	_response->root = location->configuration->get_root() + location->endPoint;
	_response->cgi = location->configuration->get_cgi();
	_response->index = location->configuration->get_index();
	_response->autoindex = location->configuration->get_autoIndex();
	_response->clientMaxBodySize = location->configuration->get_clientMaxBodySize();

}

/* ************************************************************************** */
/*								init										  */
/* ************************************************************************** */
bool	Server::responseLocation(std::string endpoint , std::string& locationName)
{
	try {
		const t_location*	location = _response->locations.at(locationName);

		write_debug_prefix("responseLocation: ", locationName);
		if (hasRedirection(location))
			return (responseRedirect(location->configuration->get_return()));
		if (createRootLocation(location) == false)
			return (responseClientError("500", getErrorPageMap("500")));
		updateResponseLocation(location);
		if (checkMethodSupported(location->configuration->get_limit_except()) == false)
			return (responseClientError("405", getErrorPageMap("405")));
		if (isRequerimentFile(endpoint))
			return (responseFileLocation(location, endpoint));
		if (isValidLocation(endpoint, locationName) == false)
			return (responseClientError("404", getErrorPageMap("404")));
		return (returnIndexLocation());
	} catch (std::exception& e) {
		write_error("responseLocation: " + std::string(e.what()));
		return (responseClientError("500", getErrorPageMap("500")));
	}
}

bool	Server::returnIndexLocation( void )
{
	auxReadFiles	tmp;

	bzero(&tmp, sizeof(tmp));
	if (generetePathToResponse(tmp.path, _response->root, _response->index) == false)
		return (sendAutoindex(_response->autoindex, _response->root));
	if (isPostMethod())
	{
		setenv("SCRIPT_FILENAME", tmp.path.c_str(), 1);
		return (handleScriptPOST());
	}
	return (responseClient(tmp, _response->cgi, "200 OK"));
}
