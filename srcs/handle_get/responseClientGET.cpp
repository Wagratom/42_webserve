/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientGET.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 09:32:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint)
{
	size_t lastSlashPos;

	while (true)
	{
		if (locations.find(endPoint) != locations.end())
			return true;
		lastSlashPos = endPoint.find_last_of('/', endPoint.length() - 2);
		if (lastSlashPos == std::string::npos || lastSlashPos == 0)
			return false;
		endPoint.erase((lastSlashPos + 1));
	}
}


bool	Server::responseClientWithInput(std::string endPoint)
{
	size_t		questionMarkPos	= endPoint.find("?");

	if (questionMarkPos == std::string::npos)
		return (write_error("Error: questionMarkPos not found"));
	std::string	scriptHandler	= "." + endPoint.substr(0, questionMarkPos);
	std::string query_string	= endPoint.substr(questionMarkPos + 1);

	setenv("QUERY_STRING", query_string.c_str(), 1);
	setenv("SCRIPT_FILENAME", scriptHandler.c_str(), 1);
	setenv("SCRIPT_NAME", "#!/usr/bin/php-cgi", 1);
	setenv("PATH_INFO", scriptHandler.c_str(), 1);
	setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
	setenv("REDIRECT_STATUS", "200", 1);
	int pid = fork();
	if (pid == -1)
		return (write_error("Error: fork() failed"));
	if (pid == 0)
		execlp(scriptHandler.c_str(), scriptHandler.c_str(), NULL);
	return (true);
}

bool	Server::responseClientGET( std::string& endPoint)
{
	std::string	LocationsNames = endPoint + "/";

	if (endPoint == "/")
		return (responseServer("200"));
	if (endPoint.find("?") != std::string::npos)
		return (responseClientWithInput(endPoint));
	if (endPoint == "/list/files/server")
		return (responseClientListFiles("/home/wallas/42_webserve/uploads/", "./root/listFiles.php"));
	if (findLocationVector(location(), LocationsNames))
		return (responseLocation(endPoint, LocationsNames));
	return (responseFileServer(endPoint));
}
