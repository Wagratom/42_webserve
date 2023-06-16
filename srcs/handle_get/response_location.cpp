/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_location.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/16 18:20:19 by wwallas-         ###   ########.fr       */
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

bool	Server::response_location(t_location_settings* location)
{
	aux_read_file	tmp;
	std::string		root = location->configuration->get_root();

	if (root.empty())
		root = server()->get_root();
	if (root.empty())
		return (false);
	if (!generete_path_to_response(tmp.path, root, location->configuration->get_index()))
		return (false);
	std::cout << "root: " << root << std::endl;
	std::cout << "path: " << tmp.path << std::endl;
	if (!get_content_file(tmp))
		return (false);
	create_header_to_files(tmp, "200");
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}
