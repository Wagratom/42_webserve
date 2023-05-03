/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_requesition.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:35:31 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 20:21:53 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


int	Server::GET_requesition( void )
{
	std::ifstream	file;

	write_debug("GET request response");
	if (!open_file_index(file))
		return (404);
	if (serv_webpage(file) == false)
		return (0);
	return (true);
}

bool	Server::serv_webpage( std::ifstream& file)
{
	std::string		content_file;
	std::string		buffer;

	content_file = "HTTP/1.1 200 OK\r\n";
	content_file += "Content-Type: text/html\r\n\r\n";
	while (std::getline(file, buffer))
		content_file += buffer;
	if (send(_client_fd, content_file.c_str(), content_file.length(), 0) == -1)
		return (false);
	return (true);
}

