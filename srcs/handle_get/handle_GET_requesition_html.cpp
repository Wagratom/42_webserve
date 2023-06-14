/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition_html.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/14 13:23:44 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

/*############################################################################*/
/*                         Handle GET requesition                             */
/*############################################################################*/

bool Server::handle_GET_requesition_html( std::string& path)
{
	bool		status;
	std::string	full_path = "/var/www" + path;

	if (path == "/")
		return response_server("200");
	if (isDirectory(full_path))
		status = check_is_location(path);
	else
		status = open_required_file(path);
	if (!status)
	{
		aux_read_file tmp;

		tmp.path = "./error_pages/404_lufy_chorando.html";
		if (!get_content_file(tmp))
			return (false);
		std::string response = "HTTP/1.1 404 Not Found\r\n"
							"Content-Type: text/html\r\n\r\n";
		response += tmp.content;
		send(_client_fd, response.c_str(), response.size(), 0);
	}
	return (true);
}

bool	Server::response_server(std::string status_code)
{
	aux_read_file tmp;

	if (!generete_path_to_response(tmp.path, server()->get_root(), server()->get_index()))
		return (false);
	if (!get_content_file(tmp))
		return (false);
	create_header_to_files(tmp, status_code);
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
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

bool Server::open_required_file(std::string& path)
{
	aux_read_file tmp;

	prepare_path_server(tmp.path, path);
	if (!get_content_file(tmp))
		return (false);
	create_header_to_files(tmp, "200");
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}

bool	Server::check_is_location(std::string& path)
{
	std::cout << "check_is_location" << std::endl;
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
