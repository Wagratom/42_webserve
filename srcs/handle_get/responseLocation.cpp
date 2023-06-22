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

struct	auxGetLocation {
	std::string		endPoint;
	int				positionLocation;
};

bool	findLocationVector(const std::vector<t_location*>& locations, auxGetLocation& aux)
{
	size_t	interator = 0;

	while(interator < locations.size())
	{
		if (aux.endPoint != locations[interator]->endPoint)
		{
			interator++;
			continue;
		}
		aux.positionLocation = interator;
		return true;
	}
	return false;
}

bool	Server::responseLocation(std::string endPoint)
{
	static const std::vector<t_location*>	locations = location();
	auxReadFiles							tmp;
	auxGetLocation							tmp2;
	std::string								root;

	std::cout << "responseLocation" << std::endl;
	appendBar(endPoint);
	tmp2.endPoint = endPoint;
	tmp2.positionLocation = -1;
	if (findLocationVector(locations, tmp2) == false)
		return (false);
	if (createRootLocation(root, locations[tmp2.positionLocation]) == false)
		return (false);
	if (generetePathToResponse(tmp.path, root, locations[tmp2.positionLocation]->configuration->get_index()) == false)
		return (false);
	if (getContentFile(tmp) == false)
		return (false);
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.response));
}
