/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseServer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 17:48:48 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::responseServer(std::string status_code)
{
	auxReadFiles						tmp;
	std::map<std::string, std::string*>	errorPages;

	errorPages = server()->get_error_page();
	if (!generetePathToResponse(tmp.path, server()->get_root(), server()->get_index()))
		return (responseClientError(ERROR500, *(errorPages.find("500")->second)));
	if (!getContentFile(tmp))
		return (responseClientError(ERROR500, *(errorPages.find("500")->second)));
	generateDynamicHeader(tmp, status_code);
	tmp.response = tmp.header + tmp.content + "\r\n";
	if (sendResponseClient(tmp.response) == false)
		return (responseClientError(ERROR500, *(errorPages.find("500")->second)));
	return (true);
}
