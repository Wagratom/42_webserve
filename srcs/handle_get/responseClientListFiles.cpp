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

bool	Server::responseClientListFiles( std::string pathDir, std::string script)
{
	std::string	response;
	std::string	listFiles;

	std::cout << "responseClientListFiles" << std::endl;
	setenv("SCRIPT_FILENAME", script.c_str(), 1);
	setenv("SCRIPT_NAME", " /usr/bin/php-cgi", 1);
	setenv("DOCUMENT_ROOT", pathDir.c_str(), 1);
	if (generateResponse(response) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	std::cout << "response: " << response << std::endl;
	return (sendResponseClient(response));
}
