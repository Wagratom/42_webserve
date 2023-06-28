/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateHeaders.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:08:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/28 10:55:56 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <sys/stat.h>

/*############################################################################*/
/*                           createDinamicHeader                              */
/*############################################################################*/
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

void	generateDynamicHeader(auxReadFiles& tmp, std::string status_code)
{
	tmp.header = "HTTP/1.1 " + status_code +" OK\r\n";
	tmp.header += "Content-Type: " + getContentType(tmp.path) + "\r\n\r\n";

}

/*############################################################################*/
/*                           createStaticHeader                               */
/*############################################################################*/

std::string	generateHeaderDynamicStatus(std::string status)
{
	std::string	header = "HTTP/1.1 " + status + " \r\n";
	header += "Content-Type: text/html\r\n";
	header += "\r\n";
	return (header);
}

std::string	generateHeaderRedirect(std::string status, std::string endPoint)
{
	std::string	header = "HTTP/1.1 " + status + " Moved Permanently\r\n";
	header += "Location: " + endPoint + "\r\n";
	header += "Content-Length: 0\r\n";
	header += "Connection: close\r\n\r\n";
	return (header);
}
