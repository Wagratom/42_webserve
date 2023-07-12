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

static bool readOutputCGI(ChildProcessData& auxProcess, std::ostringstream& oss)
{
	ssize_t				bytesRead;
	char				buffer[4096];

	close(auxProcess.fd[1]);
	while ((bytesRead = read(auxProcess.fd[0], buffer, sizeof(buffer))) > 0) {
		oss.write(buffer, bytesRead);
	}
	close(auxProcess.fd[0]);
	if (bytesRead == -1) {
		return false;
	}
	return true;
}

static bool	repairStatusCGI( std::string content, std::string& contentFormated )
{
	if (content.find("Status") != std::string::npos && content.find("Status: 200") == std::string::npos)
		return (false);
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

bool	readOuputFormatedCGI(ChildProcessData& auxProcess, std::string& dst)
{
	std::ostringstream	oss;

	if (readOutputCGI(auxProcess, oss) == false)
		return (write_error("Error: readOutputCGI"));
	if (repairStatusCGI(oss.str(), dst) == false)
		return (write_error("Error: repairStatusCGI"));
	return (true);
}
