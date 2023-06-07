/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/11 21:00:50 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

bool	Server::response_location(t_location_settings* location)
{
	aux_read_file	tmp;
	std::string		root = location->configuration->get_root();

	std::cout << "root: " << root << std::endl;
	if (root.empty())
		root = server()->get_root();
	if (root.empty())
		return (false);
	if (!generete_path_to_response(tmp.path, root, location->configuration->get_index()))
		return (false);
	std::cout << "path: " << tmp.path << std::endl;
	if (!get_content_file(tmp))
		return (false);
	create_header(tmp);
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}
