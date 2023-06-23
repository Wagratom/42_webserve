/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseFile.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 19:02:50 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

std::string	Server::GetErrorPageMapServer(std::string Error)
{
	std::map<std::string, std::string*>::iterator it;

	it = server()->get_error_page().find(Error);
	if (it == server()->get_error_page().end())
		return ("");
	return (*(it->second));
}

bool Server::responseFile(std::string endPoint)
{
	auxReadFiles	tmp;

	std::cout << "responseFile" << std::endl;
	endPoint.erase(0, 1);
	tmp.path = server()->get_root() + endPoint;
	if (getContentFile(tmp) == false)
		return (responseClientError(ERROR404, GetErrorPageMapServer("404")));
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	if (sendResponseClient(tmp.response) == false)
		return (responseClientError(ERROR_INTERNAL, GetErrorPageMapServer("500")));
	return true;
}
