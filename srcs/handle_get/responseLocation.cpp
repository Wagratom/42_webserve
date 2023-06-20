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

bool	Server::responseLocation(std::string endPoint)
{
	t_location_settings*	locations = location();
	auxReadFiles			tmp;
	std::string				root;

	std::cout << "responseLocation" << std::endl;
	appendBar(endPoint);
	if (checkValidLocation(locations, endPoint) == false)
		return (false);
	if (createRootLocation(root, locations) == false)
		return (false);
	if (!generetePathToResponse(tmp.path, root, locations->configuration->get_index()))
		return (false);
	if (getContentFile(tmp) == false)
		return (false);
	generateDynamicHeader(tmp, "200");
	tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.response));
}
