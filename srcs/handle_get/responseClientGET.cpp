/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientGET.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 09:32:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint)
{
	size_t lastSlashPos;

	while (true)
	{
		if (locations.find(endPoint) != locations.end())
			return true;
		lastSlashPos = endPoint.find_last_of('/', endPoint.length() - 2);
		if (lastSlashPos == std::string::npos || lastSlashPos == 0)
			return false;
		endPoint.erase((lastSlashPos + 1));
	}
}

bool	Server::responseClientGET( std::string& endPoint)
{
	std::string	LocationsNames = endPoint + "/";

	std::cout << "responseClientGET" << std::endl;
	if (endPoint == "/")
		return (responseServer("200"));
	if (endPoint == "/list/files/server")
		return (responseClientListFiles("uploads/"));
	if (findLocationVector(location(), LocationsNames))
		return (responseLocation(endPoint, LocationsNames));
	return (responseFileServer(endPoint));
}
