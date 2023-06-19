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
#include <sstream>
#include <iostream>
#include <sys/stat.h>

bool	getContentFile(aux_read_file& dst)
{
	std::ifstream file(dst.path.c_str(), std::ios::binary | std::ios::ate);

	std::cout << "getContentFile" << std::endl;
	if (!file.is_open())
		return (false);
	dst.size = file.tellg();
	file.seekg(0, std::ios::beg);
	dst.content.resize(dst.size);
	if (!file.read(&dst.content[0], dst.size))
		return (false);
	return (true);
}

bool	Server::createRootLocation(std::string& dst, t_location_settings* location)
{
	std::string	root = location->configuration->get_root();
	std::string	name = location->locationName;

	if (root.empty())
		root = server()->get_root();
	if (root.empty())
		return (write_error("Error: root not found"));
	if (name[0] == '/')
		name.erase(0, 1);
	dst = root + name;
	return (true);
}

void	appendBar(std::string& str)
{
	if (str[str.length() - 1] != '/')
		str.append("/");
}

bool	checkValidLocation(t_location_settings*& locations, std::string endPoint)
{
	while(locations)
	{
		if (endPoint == locations->locationName)
			return (true);
		locations = locations->next;
	}
	return (false);
}
