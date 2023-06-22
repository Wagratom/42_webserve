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

bool findLocationVector(const std::map<std::string, t_location*> &locations, std::string endPoint)
{
	if (locations.find(endPoint) != locations.end())
		return true;
	if (locations.begin()->second->endPoint == endPoint)
		return true;
	return false;
}

bool	Server::responseLocation(std::string endPoint)
{
	appendBar(endPoint);
	static const std::map<std::string, t_location*>	locations = location();
	auxReadFiles									tmp;
	std::string										root;
	const t_location* const							location = locations.at(endPoint);

	std::cout << "responseLocation" << std::endl;
	if (findLocationVector(locations, endPoint) == false)
		return (false);
	if (createRootLocation(root, location) == false)
		return (false);
	if (generetePathToResponse(tmp.path, root, location->configuration->get_index()) == false)
		return (false);
	if (getContentFile(tmp) == false)
		return (false);
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.response));
}
