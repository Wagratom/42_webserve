/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/21 10:16:05 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handlePostRequest()
{
	std::string	endPoint = _parserRequest->get_endPoint();
	std::string	LocationsNames = _parserRequest->get_endPoint();

	write_debug_prefix(CIANO, "\t Tratavive request");
	write_debug(AZUL);
	write_debug("handlePostRequest");
	if (findLocationVector(_serverUsing->get_locations(), LocationsNames))
		return responseLocation(endPoint, LocationsNames);
	std::string	script = endPoint.erase(0, 1);
	setenv("SCRIPT_FILENAME", std::string(_serverUsing->get_root() + script).c_str(), 1);
	return handleScriptPOST();
}
