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

static void	addPrefixListFiles(std::string& listFiles)
{
	listFiles = "listFiles=" + listFiles;
}

bool	Server::responseClientListFiles()
{
	std::string	response;
	std::string	listFiles;

	if (generateFilesList(listFiles) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	addPrefixListFiles(listFiles);
	if (generateResponse(listFiles, response) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (sendResponseClient(response));
}
