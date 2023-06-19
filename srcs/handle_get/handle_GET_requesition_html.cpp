/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition_html.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 18:10:26 by wwallas-         ###   ########.fr       */
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
		return responseServer("200");
	if (isDirectory(full_path))
		return (responseLocation(endPoint));
	return (responseFile(endPoint));
}

bool Server::responseFile(std::string endpoint)
{
	aux_read_file tmp;

	std::cout << "responseFile" << std::endl;
	tmp.path = server()->get_root() + endpoint;
	if (!get_content_file(tmp))
		return (false);
	create_header_to_files(tmp, "200");
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}

bool	Server::responseLocation(std::string& path)
{
	std::cout << "responseLocation" << std::endl;
	t_location_settings* locations = location();

	if (path[path.length() - 1] != '/')
		path.append("/");
	while(locations)
	{
		if (path == locations->locationName)
			return responseLocation(locations);
		locations = locations->next;
	}
	return (false);
}
