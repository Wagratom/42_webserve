/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/30 14:15:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handlePostRequest()
{
	std::string	endPoint = _parserRequest->get_endPoint();
	std::string	LocationsNames = _parserRequest->get_endPoint();

	write_debug("handlePostRequest");
	_response->method = "POST";
	if (findLocationVector(_serverUsing->get_locations(), LocationsNames))
		return responseLocation(endPoint, LocationsNames);
	std::string	script = endPoint.erase(0, 1);
	_response->errorMap = _serverUsing->get_error_page();
	setenv("SCRIPT_FILENAME", std::string(_serverUsing->get_root() + script).c_str(), 1);
	return handleScriptPOST();
}
