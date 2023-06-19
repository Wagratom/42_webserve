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
	t_location_settings* locations = location();

	std::cout << "responseLocation" << std::endl;
	void (appendBar(endPoint));
	if (checkValidLocation(locations, endPoint) == false)
		return (false);
	return (responseLocation(locations));
}

bool	Server::responseLocation(t_location_settings* location)
{
	aux_read_file	tmp;
	std::string		root;

	if (createRootLocation(root, location) == false)
		return (false);
	if (!generetePathToResponse(tmp.path, root, location->configuration->get_index()))
		return (false);
	if (getContentFile(tmp) == false)
		return (false);
	create_header_to_files(tmp, "200");
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}
