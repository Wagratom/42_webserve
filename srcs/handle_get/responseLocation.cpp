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

bool	Server::createRootLocation(std::string& dst, const t_location* location)
{
	dst = location->configuration->get_root();
	if (dst.empty())
		dst = server()->get_root();
	if (dst.empty())
		return (write_error("Error: root not found"));
	return (true);
}

bool	Server::responseLocation(std::string endPoint, std::string locationName)
{
	t_location*							_location = location().at(locationName);

	std::cout << "responseLocation" << std::endl;
	if (_location == NULL)
		return (responseClientError(ERROR500, getErrorPageMapLocation(_location, "500")));
	if (hasRedirection(_location))
		return (responseRedirect(_location->configuration->get_return()));
	if (isRequerimentFile(endPoint))
		return (responseFileLocation(_location, endPoint));
	if (isEndPoint(endPoint, locationName))
		return (returnIndexLocation(_location));
	return (responseClientError(ERROR404, getErrorPageMapLocation(_location, "404")));
}

bool	Server::returnIndexLocation(t_location* location)
{
	auxReadFiles						tmp;
	std::string							root;

	std::cout << "returnIndexLocation" << std::endl;
	if (createRootLocation(root, location) == false)
		return (responseClientError(ERROR500, getErrorPageMapLocation(location, "500")));
	if (generetePathToResponse(tmp.path, root, location->configuration->get_index()) == false)
		return (responseAutoIndexOrErrorLocation(location));
	if (getContentFile(tmp) == false)
		return (responseClientError(ERROR500, getErrorPageMapLocation(location, "500")));
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.response));
}

bool	Server::responseAutoIndexOrErrorLocation( t_location* location )
{
	std::cout << "responseAutoIndexOrErrorLocation" << std::endl;
	if (location->configuration->get_autoIndex() == false)
		return (responseClientError(ERROR500, *(location->configuration->get_error_page().find("404")->second)));
	if (responseClientListFiles(location->configuration->get_root().c_str(), "./root/autoindex.php") == false)
		return (responseClientError(ERROR500, *(location->configuration->get_error_page().find("404")->second)));
	return (true);

}
