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

/*############################################################################*/
/*                         Handle GET requesition                             */
/*############################################################################*/

struct aux_read_file
{
	std::string			content;
	std::string			path;
	std::streamsize		size;
	std::ostringstream	oss;
	std::string			header;
};

bool Server::handle_GET_requesition_html( std::string& path)
{
	if (path == "/")
		return open_server_index();
	else
		return open_required_file(path);
	return (true);
}

static bool	get_content_file(aux_read_file& dst)
{
	std::ifstream file(dst.path.c_str(), std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return (false);
	dst.size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::cout << "size: " << dst.size << std::endl;
	dst.content.resize(dst.size);
	if (!file.read(&dst.content[0], dst.size))
		return (false);
	return (true);
}

bool	Server::open_server_index( void )
{
	aux_read_file tmp;

	if (!generete_path_to_response(tmp.path))
		return (false);
	if (!get_content_file(tmp))
		return (false);
	tmp.oss << tmp.size;
	tmp.header = "HTTP/1.1 200 OK\r\n";
	tmp.header += "Content-Type: text/html\r\n";
	tmp.header += "Content-Length: " + tmp.oss.str() + "\r\n\r\n";
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}

bool Server::open_required_file(std::string& path)
{
	aux_read_file tmp;
	tmp.path = path;

	if (get_content_file(tmp))
	{
		execve("/usr/bin/php-cgi7.4", NULL, NULL);
		tmp.header = "HTTP/1.1 200 OK\r\n";
		tmp.header += "Content-Type: text/html\r\n";
		tmp.header += "Content-Length: " + tmp.oss.str() + "\r\n\r\n";
		tmp.oss << tmp.size;
		send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
		send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	}
	else
	{
		tmp.header = "HTTP/1.1 404 Not Found\r\n";
		tmp.header += "Content-Type: image/x-icon\r\n";
		tmp.content = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
		send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
		send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	}
	return (true);
}
