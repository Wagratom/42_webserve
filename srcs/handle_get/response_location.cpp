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


bool	Server::get_root_location(std::string& root, const std::string& path)
{
	size_t	pos = path.find_last_of('/');
	if (pos == std::string::npos)
		return (false);
	root = path.substr(0, pos);
	return (true);
}

bool	get_content_file(aux_read_file& dst)
{
	std::ifstream file(dst.path.c_str(), std::ios::binary | std::ios::ate);

	std::cout << "get_content_file" << std::endl;
	if (!file.is_open())
		return (false);
	dst.size = file.tellg();
	file.seekg(0, std::ios::beg);
	dst.content.resize(dst.size);
	if (!file.read(&dst.content[0], dst.size))
		return (false);
	return (true);
}

static std::string	create_root_location(std::string rootLocation, std::string rootServer, std::string locationName)
{
	std::string		root = rootLocation;

	if (root.empty())
		root = rootServer;
	if (root.empty())
		return ("");
	if (root[root.size() - 1] != '/')
		root += "/";
	root += locationName;
	return (root);
}

bool	Server::responseLocation(t_location_settings* location)
{
	aux_read_file	tmp;
	std::string		root;

	root = create_root_location(location->configuration->get_root(), server()->get_root(), location->locationName);
	if (!generete_path_to_response(tmp.path, root, location->configuration->get_index()))
		return (false);
	if (get_content_file(tmp) == false)
		return (false);
	create_header_to_files(tmp, "200");
	std::cout << "Header" << std::endl;
	std::cout << "header: " << tmp.header << std::endl;
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}
