/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliaries.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:08:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 16:51:58 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <sys/stat.h>

static std::map<std::string, std::string>	generete_dictionary_type()
{
	static std::map<std::string, std::string> types;

	types[".html"] = "text/html";
	types[".php"] = "text/html";
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

bool	isDirectory(const std::string& path)
{
	struct stat fileStat;
	if (stat(path.c_str(), &fileStat) == 0) {
		return (fileStat.st_mode & S_IFDIR) != 0;
	}
	return false;
}

void	create_header_to_files(aux_read_file& tmp, std::string status_code)
{
	tmp.oss << tmp.size;
	tmp.header = "HTTP/1.1 " + status_code +" OK\r\n";
	tmp.header += "Content-Type: " + getContentType(tmp.path) + "\r\n";
	tmp.header += "Content-Length: " + tmp.oss.str() + "\r\n\r\n";
}


std::string	create_header_html(std::string status_code)
{
	std::string header =	"HTTP/1.1 " + status_code +" OK\r\n";
	header += "Content-Type: text/html \r\n";
	header += "\r\n";
	return (header);
}

std::string	create_header_404( void )
{
	std::string	header = "HTTP/1.1 404 Not Found\r\n";
	header += "Content-Type: text/html\r\n\r\n";
	header += "\r\n";
	return (header);
}

std::string	create_header_400( void )
{
	std::string	header = "HTTP/1.1 400 Bad Request\r\n";
	header += "Content-Type: text/html\r\n\r\n";
	header += "\r\n";
	return (header);
}

std::string	create_header_500( void )
{
	std::string	header = "HTTP/1.1 500 Internal Server\r\n";
	header += "Content-Type: text/html\r\n\r\n";
	header += "\r\n";
	return (header);
}
