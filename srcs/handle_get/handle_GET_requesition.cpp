/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/03 10:32:48 by wwallas-         ###   ########.fr       */
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

bool	Server::handle_GET_requesition( void )
{
	std::string locationName = _parserRequest->get_endPoint();

	write_debug_prefix(CIANO, "\t Tratavive request");
	write_debug(AZUL);
	write_debug("handle_GET_requesition");
	_response->method = "GET";
	if (locationName == "/")
		return (responseServer());
	if (locationName.find("?") != std::string::npos)
		handleQuerystring(locationName);
	std::string copy = locationName;
	if (findLocationVector(_response->locations, locationName))
		return (responseLocation(_parserRequest->get_endPoint(), locationName));
	return (responseFileServer(copy));
}
