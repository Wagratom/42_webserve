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

bool	Server::createRootLocation(std::string& dst, const t_location* location)
{
	dst = location->configuration->get_root();
	if (dst.empty())
		dst = server()->get_root();
	if (dst.empty())
		return (write_error("Error: root not found"));
	return (true);
}

bool	Server::returnIndexLocation(t_location* location)
{
	auxReadFiles						tmp;
	std::string							root;

	std::cout << "returnIndexLocation" << std::endl;
	if (createRootLocation(root, location) == false)
		return (responseClientError(ERROR_INTERNAL, getErrorPageMapLocation(location, "500")));
	if (generetePathToResponse(tmp.path, root, location->configuration->get_index()) == false)
		return (responseClientError(ERROR404, getErrorPageMapLocation(location, "500")));
	if (getContentFile(tmp) == false)
		return (responseClientError(ERROR_INTERNAL, getErrorPageMapLocation(location, "500")));
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.response));
}

bool	Server::responseLocation(std::string endPoint, std::string locationName)
{
	t_location*							_location = location().at(locationName);

	std::cout << "responseLocation" << std::endl;
	if (endPoint.find(".") != std::string::npos)
		return (responseFileLocation(_location, endPoint));
	if (endPoint[endPoint.length() - 1] != '/')
		endPoint += "/";
	if (endPoint == locationName)
		return (returnIndexLocation(_location));
	return (responseClientError(ERROR404, getErrorPageMapLocation(_location, "404")));
}
