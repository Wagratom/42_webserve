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
	std::string header;

	if (spacePos == std::string::npos)
		return (write_error("Error: responseRedirect"));
	header = generateHeaderRedirect(endPoint.substr(0, spacePos), endPoint.substr(spacePos + 1));
	if (sendResponseClient(header) == false)
		return (write_error("Error: responseRedirect"));
	return (true);
}
