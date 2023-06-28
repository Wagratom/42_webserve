/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateListFiles.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/28 17:53:43 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

// static bool	openDirectorUpdate(DIR*& dir, const char* pathDir)
// {
// 	dir = opendir(pathDir);
// 	return (dir != NULL);
// }

// static bool	createFileList(DIR*& dir, std::string& listFiles)
// {
// 	struct dirent	*ent;

// 	while ((ent = readdir(dir)) != NULL)
// 	{
// 		if (std::string(ent->d_name) == "." || std::string(ent->d_name) == "..")
// 			continue ;
// 		listFiles += ent->d_name;
// 		listFiles += "\n";
// 	}
// 	return (true);
// }

// bool	generateFilesList(std::string& listFiles, const char* pathDir)
// {
// 	DIR	*dir;

// 	std::cout << "generateFilesList" << std::endl;
// 	if (openDirectorUpdate(dir, pathDir) == false)
// 		return (write_error("Error: generateFilesList: opening directory"));
// 	return (createFileList(dir, listFiles));
// }
