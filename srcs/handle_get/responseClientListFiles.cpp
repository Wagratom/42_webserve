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

bool	Server::responseClientListFiles( std::string pathDir, std::string pathFile)
{
	std::string	response;
	std::string	listFiles;

	std::cout << "responseClientListFiles" << std::endl;
	setenv("PATHFILE", pathFile.c_str(), 1);
	setenv("PATHDIR", pathDir.c_str(), 1);
	// if (generateFilesList(listFiles, pathDir.c_str()) == false)
		// return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	if (generateResponse(listFiles, response) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	std::cout << "response: " << response << std::endl;
	return (sendResponseClient(response));
}
