/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateHeaders.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:08:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:43 by wwallas-         ###   ########.fr       */
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

/*############################################################################*/
/*                           createStaticHeader                               */
/*############################################################################*/

void	generateHeaderDynamicStatus(auxReadFiles& dst, std::string status)
{
	std::ostringstream oss;
	oss << dst.content.length(); // Convertendo o valor numérico para uma string usando std::ostringstream

	dst.header = "HTTP/1.1 " + status + " \r\n";
	dst.header += "Content-Type: " + getContentType(dst.path) + "\r\n";
	dst.header += "Content-Length: " + oss.str() + "\r\n\r\n";
}

std::string	generateHeaderRedirect(std::string status, std::string endPoint)
{
	std::string	header = "HTTP/1.1 " + status + " Moved Permanently\r\n";
	header += "Location: " + endPoint + "\r\n";
	header += "Content-Length: 0\r\n";
	header += "Connection: close\r\n\r\n";
	return (header);
}
