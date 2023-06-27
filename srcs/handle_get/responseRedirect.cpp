/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseLocation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::responseRedirect(std::string endPoint)
{
	size_t spacePos = endPoint.find(" ");

	if (spacePos == std::string::npos)
		return (write_error("Error: responseRedirect"));
	std::string	response = "HTTP/1.1 " + endPoint.substr(0,3) + " Moved Permanently\r\n";
	response += "Location: " + endPoint.substr(spacePos + 1) + "\r\n";
	response += "Content-Length: 0\r\n";
	response += "Connection: close\r\n\r\n";
	std::cout << "responseRedirect: " << response << std::endl;
	if (send(_client_fd, response.c_str(), response.length(), 0) == -1)
		return (write_error("Error: send responseRedirect"));
	return (true);
}
