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
#include <sys/stat.h>

static bool	hasRedirection(const t_location*& location)
{
	return (location->configuration->get_return().empty() == false);
}

static void removeQueryString(std::string& endPoint)
{
	size_t	questionMarkPos = endPoint.find("?");

	if (questionMarkPos == std::string::npos)
		return ;
	endPoint.erase(questionMarkPos);
}

static bool	isPostMethod( void )
{
	if (std::string(getenv("REQUEST_METHOD")) == "POST")
		return (true);
	return (false);
}

bool	Server::createRootLocation(const t_location*& location, bool& is_location_server)
{
	const std::string& root = location->configuration->get_root();

	if (root.empty() && _response->root.empty())
		return write_error("Error: root not found");
	if (root.empty())
		is_location_server = true;
	else
		_response->root = root;
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

void	Server::updateResponseLocation(const t_location*& location, bool& is_location_server)
{
	_response->errorPage = location->configuration->get_error_page();
	if (_response->root[0] == '.' && _response->root[1] == '/' && is_location_server == false)
		_response->root = _response->root + location->endPoint;
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
	write_debug_prefix("responseLocation: ", locationName);
	try {
		const t_location*	location = _response->locations.at(locationName);
		bool				is_location_server;

		is_location_server = false;
		if (hasRedirection(location))
			return (responseRedirect(location->configuration->get_return()));
		if (createRootLocation(location, is_location_server) == false)
			return (responseClientError("500", getErrorPageMap("500")));
		updateResponseLocation(location, is_location_server);
		if (checkMethodSupported(location->configuration->get_limit_except()) == false)
			return (responseClientError("405", getErrorPageMap("405")));
		endpoint.erase(0, locationName.length());
		return (handle_request_location(location, endpoint));
	} catch (std::exception& e) {
		write_error("responseLocation: " + std::string(e.what()));
		return (responseClientError("500", getErrorPageMap("500")));
	}
}

bool	Server::handle_request_location(const t_location*& location, std::string& order)
{
	write_debug("handle_request_location");
	removeQueryString(order);
	if (order[0] == '/')
		order.erase(0, 1);
	std::string path = _response->root + order;
	std::cout << "path: " << path << std::endl;
	struct stat file_stat;
	if (stat(path.c_str(), &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			_response->root = path;
			if (_response->root[_response->root.length() - 1] != '/')
				_response->root += "/";
			return (returnIndexLocation());
		}
		else
			return (responseFileLocation(location, path));
	}
	else {
		responseClientError("404", getErrorPageMap("404"));
	}
	return false;
}


bool	Server::returnIndexLocation( void )
{
	auxReadFiles	tmp;

	write_debug("returnIndexLocation");
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
