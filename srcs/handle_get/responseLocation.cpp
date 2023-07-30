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
	std::string	rootServer = _serverUsing->get_root();
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

/*								init										  */
/* ************************************************************************** */
bool	Server::responseLocation(std::string& endPoint, std::string& locationName)
{
	try {
		const t_location*	location = _serverUsing->get_locations().at(locationName);

		write_debug_prefix("responseLocation: ", locationName);
		_response->errorMap = location->configuration->get_error_page();
		if (checkMethodSupported(location->configuration->get_limit_except()) == false)
			return (responseClientError(ERROR405, location->configuration->get_root(), getErrorPageMap(_response->errorMap, "405")));
		if (createRootLocation(location) == false)
			return (responseClientError(ERROR500, location->configuration->get_root(), getErrorPageMap(_response->errorMap, "500")));
		if (hasRedirection(location))
			return (responseRedirect(location->configuration->get_return()));
		if (isRequerimentFile(endPoint))
			return (responseFileLocation(location, endPoint));
		if (isEndPoint(endPoint, locationName))
			return (returnIndexLocation(location));
		return (responseClientError(ERROR404, location->configuration->get_root(), getErrorPageMap(_response->errorMap, "404")));
	} catch (std::exception& e) {
		write_error("responseLocation: " + std::string(e.what()));
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "500")));
	}
}

bool	Server::responseLocationPost(const t_location*& location)
{
	std::string path;
	Location_configuration*	locationConf = location->configuration;

	write_debug("responseLocationPost");
	if (generetePathToResponse(path, locationConf->get_root(), locationConf->get_index()) == false)
		return sendAutoindex(locationConf->get_autoIndex(), locationConf->get_root());
	setenv("SCRIPT_FILENAME", path.c_str(), 1);
	return handleScriptPOST();
}

bool	Server::returnIndexLocation(const t_location*& location)
{
	Location_configuration*	locationConf = location->configuration;
	auxReadFiles			tmp;

	bzero(&tmp, sizeof(tmp));
	write_debug("returnIndexLocation");
	if (generetePathToResponse(tmp.path, locationConf->get_root(), locationConf->get_index()) == false)
		return (sendAutoindex(locationConf->get_autoIndex(), locationConf->get_root()));
	if (isPostMethod())
		return (handleScriptPOST());
	return (responseClient(tmp, locationConf->get_cgi(), "200 OK"));
}
