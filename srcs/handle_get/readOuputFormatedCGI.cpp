/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientListFiles.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 19:01:02 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <sstream>

static bool readOutputCGI(const ChildProcessData& auxProcess, std::ostringstream& oss)
{
	ssize_t	bytesRead;
	char	buffer[4096];

	while ((bytesRead = read(auxProcess.fd[0], buffer, sizeof(buffer))) > 0) {
		oss.write(buffer, bytesRead);
	}
	close(auxProcess.fd[0]);
	if (bytesRead == -1)
		return write_error("readOutputCGI: bytesRead == -1");
	return true;
}

static bool	repairStatusCGI( std::string content, std::string& contentFormated )
{
	if (content.empty())
		return (write_error("Script Output is empty"));
	if (content.find("Status") != std::string::npos && content.find("Status: 200") == std::string::npos)
		return (write_error("Script Output is not 200"));
	if (content.find("Status: 200") != std::string::npos)
	{
		size_t pos = content.find("Status: 200");
		content.erase(pos, 12);
		contentFormated = "HTTP/1.1 200 OK\r\n" + content;
	}
	else if (content.find("Status: 200") == std::string::npos)
		contentFormated = "HTTP/1.1 200 OK\r\n" + content;
	return (true);
}

bool	readOuputFormatedCGI(std::string& dst, const ChildProcessData& auxProcess)
{
	std::ostringstream	oss;

	write_debug("readOuputFormatedCGI");
	if (readOutputCGI(auxProcess, oss) == false)
		return (false);
	if (repairStatusCGI(oss.str(), dst) == false)
		return (false);
	return (true);
}
