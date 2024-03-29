/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/16 18:57:20 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handlePostRequest()
{
	std::string	locationName = _parserRequest->get_endPoint();
	std::string	endpoint = _parserRequest->get_endPoint();


	write_debug("handlePostRequest");
	_response->method = "POST";
	if (findLocationVector(_response->locations, locationName))
		return responseLocation(_parserRequest->get_endPoint(), locationName);
	setenv("SCRIPT_FILENAME", std::string(_response->root + endpoint).c_str(), 1);
	return handleScriptPOST();
}
