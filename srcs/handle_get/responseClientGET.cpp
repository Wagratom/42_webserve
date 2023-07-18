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

void	Server::handleQuerystring(std::string& endPoint)
{
	size_t	questionMarkPos = endPoint.find("?");

	if (questionMarkPos == std::string::npos)
		return ;
	setenv("QUERY_STRING", endPoint.substr(questionMarkPos + 1).c_str(), 1);
	endPoint.erase(questionMarkPos);
}

bool	Server::responseClientGET( std::string& endPoint)
{
	std::string	LocationsNames = endPoint;

	if (endPoint == "/")
		return (responseServer());
	if (endPoint.find("?") != std::string::npos)
		handleQuerystring(endPoint);
	if (findLocationVector(_serverUsing->get_locations(), LocationsNames))
		return (responseLocation(endPoint, LocationsNames));
	return (responseFileServer(endPoint));
}
