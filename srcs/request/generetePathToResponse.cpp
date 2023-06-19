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

static bool	open_file_status( std::string path )
{
	std::ifstream	file(path.c_str());

	std::cout << "path: " << path << std::endl;
	if (!file.is_open())
		return (false);
	std::cout << "File opened" << std::endl;
	return (true);
}

static std::string	GeneratePathFile( std::string root, std::string filename )
{
	return (std::string(root + filename));
}

static bool	saveValidPathFile(std::string& pathFile, std::string currentPath)
{
	if (!open_file_status(currentPath))
		return (false);
	pathFile = currentPath;
	return (true);
}

static bool getValidPath(std::string listNames, std::string root, std::string& pathFile)
{
	size_t	pos;

	while ((pos = listNames.find_first_of(" \t")) != std::string::npos)
	{
		std::string currentPath = GeneratePathFile(root, listNames.substr(0, pos));
		if (saveValidPathFile(pathFile, currentPath))
			return true;
		listNames.erase(0, (pos + 1));
	}
	pathFile = GeneratePathFile(root, listNames);
	return (saveValidPathFile(pathFile, pathFile));
}

bool	Server::generetePathToResponse(std::string& dst, std::string root, std::string listNames)
{
	dst.clear();
	if (listNames.empty() || root.empty())
		return (write_error("Error: root or listNames is empty"));
	return (getValidPath(listNames, root, dst));
}

