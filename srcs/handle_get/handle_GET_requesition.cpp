/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/02 13:28:14 by wwallas-         ###   ########.fr       */
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
	std::string endPoint = _parserRequest->get_endPoint();

	write_debug_prefix(CIANO, "\t Tratavive request");
	write_debug(AZUL);
	write_debug("handle_GET_requesition");
	_response->method = "GET";
	if (endPoint == "/")
		return (responseServer());
	if (endPoint.find("?") != std::string::npos)
		handleQuerystring(endPoint);
	if (findLocationVector(_response->locations, endPoint))
		return (responseLocation(endPoint));
	return (responseFileServer(endPoint));
}
