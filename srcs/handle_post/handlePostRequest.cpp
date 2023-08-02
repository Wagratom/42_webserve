/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostRequest.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/02 13:22:06 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handlePostRequest()
{
	std::string	endPoint = _parserRequest->get_endPoint();

	write_debug("handlePostRequest");
	_response->method = "POST";
	if (findLocationVector(_response->locations, endPoint))
		return responseLocation(endPoint);
	setenv("SCRIPT_FILENAME", std::string(_response->root + endPoint).c_str(), 1);
	return handleScriptPOST();
}
