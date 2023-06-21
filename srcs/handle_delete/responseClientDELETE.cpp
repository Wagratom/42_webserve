/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientDELETE.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 12:57:35 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>
#include <dirent.h>

static void	addPrefixListFiles(std::string& listFiles)
{
	listFiles = "listFiles=" + listFiles;
}

bool	Server::responseClientDELETE()
{
	std::string	response;
	std::string	listFiles;

	if (generateFilesList(listFiles) == false)
		return (false);
	addPrefixListFiles(listFiles);
	if (generateResponse(listFiles, response) == false)
		return (false);
	return (sendResponseClient(response));
}
