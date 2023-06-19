/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition_html.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 17:50:20 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


/*############################################################################*/
/*                         Handle GET requesition                             */
/*############################################################################*/

bool	Server::handle_GET_requesition_html( std::string& endPoint)
{
	std::string	full_path = server()->get_root() + endPoint;

	std::cout << "handle_GET_requesition_html" << std::endl;
	if (endPoint == "/")
		return response_server("200");
	if (isDirectory(full_path))
		return (response_location(endPoint));
	return (response_file(endPoint));
}

void	Server::prepare_path_server(std::string& dst, std::string& path)
{
	if (path[0] == '.')
		path.erase(0, 1);
	if (path[0] == '/')
		path.erase(0, 1);
	path = server()->get_root() + path;
	dst = path;
}

bool Server::response_file(std::string& path)
{
	aux_read_file tmp;

	std::cout << "response_file" << std::endl;
	prepare_path_server(tmp.path, path);
	if (!get_content_file(tmp))
		return (false);
	create_header_to_files(tmp, "200");
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}

bool	Server::response_location(std::string& path)
{
	std::cout << "response_location" << std::endl;
	t_location_settings* locations = location();

	if (path[path.length() - 1] != '/')
		path.append("/");
	while(locations)
	{
		if (path == locations->locationName)
			return response_location(locations);
		locations = locations->next;
	}
	return (false);
}
