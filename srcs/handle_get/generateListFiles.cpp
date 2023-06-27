/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateListFiles.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/27 19:34:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

static bool	openDirectorUpdate(DIR*& dir, const char* pathDir)
{
	dir = opendir(pathDir);
	std::cout << "pathDir: '" << pathDir << "'" <<std::endl;
	return (dir != NULL);
}

static bool	createFileList(DIR*& dir, std::string& listFiles)
{
	struct dirent	*ent;

	while ((ent = readdir(dir)) != NULL)
	{
		if (std::string(ent->d_name) == "." || std::string(ent->d_name) == "..")
			continue ;
		listFiles += ent->d_name;
		listFiles += "\n";
	}
	return (true);
}

bool	generateFilesList(std::string& listFiles, const char* pathDir)
{
	DIR	*dir;

	if (openDirectorUpdate(dir, pathDir) == false)
		return (write_error("Error: handle_delete: opening directory"));
	return (createFileList(dir, listFiles));
}
