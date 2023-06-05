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
	if (path == "/")
		return open_server_index();
	if	(open_required_file(path))
		return (true);
	else
	{
		std::string header = "HTTP/1.1 404 Not Found\r\n"
							 "Content-Type: text/html\r\n";
		std::string content = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
		send(_client_fd, header.c_str(), header.size(), 0);
		send(_client_fd, content.c_str(), content.size(), 0);
	}
	return (true);
}

bool	Server::open_server_index( void )
{
	aux_read_file tmp;

	if (!generete_path_to_response(tmp.path))
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

	if (get_content_file(tmp))
	{
		create_header(tmp);
		send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
		send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	}

	return (true);
}
