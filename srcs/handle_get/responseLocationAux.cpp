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

bool	Server::createRootLocation(std::string& dst, std::vector<t_location*> location)
{

	dst = location[0]->configuration->get_root();
	if (dst.empty())
		dst = server()->get_root();
	if (dst.empty())
		return (write_error("Error: root not found"));
	return (true);
}

bool	Server::sendResponseClient(std::string response)
{
	if (send(_client_fd, response.c_str(), response.size(), 0) == -1)
		return (write_error("Error: handle_delete: send"));
	return (true);
}

void	appendBar(std::string& str)
{
	if (str[str.length() - 1] != '/')
		str.append("/");
}

bool	checkValidLocation(std::vector<t_location*>& locations, std::string endPoint)
{
	while(locations.size() != 0)
	{
		if (endPoint == locations[0]->endPoint)
			return (true);
		locations.erase(locations.begin());
	}
	return (false);
}
