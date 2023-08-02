/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/01 21:12:06 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handlePostRequest()
{
	std::string	endPoint = _parserRequest->get_endPoint();
	std::string	LocationsNames = _parserRequest->get_endPoint();

	write_debug("handlePostRequest");
	_response->method = "POST";
	if (findLocationVector(_response->locations, LocationsNames))
		return responseLocation(endPoint, LocationsNames);
	std::string	script = endPoint.erase(0, 1);
	_response->errorPage = _response->errorPage;
	setenv("SCRIPT_FILENAME", std::string(_response->root + script).c_str(), 1);
	return handleScriptPOST();
}
