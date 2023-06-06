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

static bool	isDirectory(const std::string& path) {
	struct stat fileStat;
	if (stat(path.c_str(), &fileStat) == 0) {
		return (fileStat.st_mode & S_IFDIR) != 0;
	}
	return false;
}
struct aux_read_file
{
	std::string			content;
	std::string			path;
	std::streamsize		size;
	std::ostringstream	oss;
	std::string			header;
};

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

static std::map<std::string, std::string>	generete_dictionary_type()
{
	static std::map<std::string, std::string> types;

	types[".html"] = "text/html";
	types[".css"] = "text/css";
	types[".js"] = "text/javascript";
	types[".png"] = "image/png";
	types[".jpg"] = "image/jpeg";
	types[".gif"] = "image/gif";
	types[".svg"] = "image/svg+xml";
	types[".ico"] = "image/x-icon";
	types[".txt"] = "text/plain";
	return (types);
}

static const std::string	getContentType(const std::string& path)
{
	static	std::map<std::string, std::string> dictionary_types = generete_dictionary_type();

	std::string extension = path.substr(path.find_last_of('.'));
	if (dictionary_types.find(extension) != dictionary_types.end())
		return (dictionary_types[extension]);
	return ("text/plain");
}

static void	create_header(aux_read_file& tmp)
{
	tmp.oss << tmp.size;
	tmp.header = "HTTP/1.1 200 OK\r\n";
	tmp.header += "Content-Type: " + getContentType(tmp.path) + "\r\n";
	tmp.header += "Content-Length: " + tmp.oss.str() + "\r\n\r\n";

}
/*############################################################################*/
/*                         Handle GET requesition                             */
/*############################################################################*/

bool Server::handle_GET_requesition_html( std::string& path)
{
	bool		status;
	std::string	full_path = "/var/www" + path;

	if (path == "/")
		return open_server_index();
	if (isDirectory(full_path))
		status = check_is_location(path);
	else
		status = open_required_file(path);
	if (!status)
	{
		std::ifstream file("error_pages/404.html");
		std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		std::cout << "Error: file not found" << std::endl;
		std::string response = "HTTP/1.1 404 Not Found\r\n"
							   "Content-Type: text/html\r\n\r\n";
		response += fileContent;
		send(_client_fd, response.c_str(), response.size(), 0);
		std::cout << "enviei" << std::endl;
	}
	return (true);
}

bool	Server::open_server_index( void )
{
	aux_read_file tmp;

	if (!generete_path_to_response(tmp.path, server()->get_root(), server()->get_index()))
		return (false);
	if (!get_content_file(tmp))
		return (false);
	create_header(tmp);
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}

bool Server::open_required_file(std::string& path)
{
	aux_read_file tmp;

	tmp.path = path;
	if (!get_content_file(tmp))
		return false ;
	create_header(tmp);
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}

bool	Server::check_is_location(std::string& path)
{
	std::cout << "check_is_location" << std::endl;
	t_location_settings* locations = location();

	path = path;
	while(locations)
	{
		if (path == locations->locationName)
			return open_server_index(locations);
		locations = locations->next;
	}
	return (false);
}

bool	Server::open_server_index(t_location_settings* location)
{
	aux_read_file tmp;
	std::string root = location->configuration->get_root();

	if (root.empty())
		root = "/var/www" + location->locationName + "/";
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
