/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliaries.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:08:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/14 15:20:25 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <sys/stat.h>

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

bool	isDirectory(const std::string& path)
{
	struct stat fileStat;
	if (stat(path.c_str(), &fileStat) == 0) {
		return (fileStat.st_mode & S_IFDIR) != 0;
	}
	return false;
}

bool	get_content_file(aux_read_file& dst)
{
	std::ifstream file(dst.path.c_str(), std::ios::binary | std::ios::ate);

	if (!file.is_open())
		return (false);
	dst.size = file.tellg();
	file.seekg(0, std::ios::beg);
	dst.content.resize(dst.size);
	if (!file.read(&dst.content[0], dst.size))
		return (false);
	return (true);
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
