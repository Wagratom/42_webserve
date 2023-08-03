/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generetePathToResponse.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:04:00 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 19:00:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	open_file_status( const std::string& path )
{
	std::ifstream	file(path.c_str());

	if (access(path.c_str(), F_OK) == -1)
		return (false);
	write_debug_prefix("Path: ", path);
	return (true);
}

static bool	saveValidPathFile(std::string& pathFile, std::string& currentPath)
{
	if (!open_file_status(currentPath))
		return (false);
	pathFile = currentPath;
	return (true);
}

static bool getValidPath(std::string& pathFile, const std::string& root, std::string listNames)
{
	std::string	currentPath;
	size_t		endWorld;

	while ((endWorld = listNames.find_first_of(" \t")) != std::string::npos)
	{
		currentPath = root + listNames.substr(0, endWorld);
		if (saveValidPathFile(pathFile, currentPath))
			return true;
		listNames.erase(0, (endWorld + 1));
	}
	pathFile = root + listNames;
	return saveValidPathFile(pathFile, pathFile);
}

bool	Server::generetePathToResponse(std::string& dst, const std::string& root, const std::string& listNames)
{
	write_debug("generetePathToResponse");
	if (listNames.empty() || root.empty())
		return (write_error("path not found"));
	if (getValidPath(dst, root, listNames) == false)
		return (write_error("path not found"));
	return (true);
}

