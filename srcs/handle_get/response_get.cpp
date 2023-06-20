/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_get.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 21:27:03 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendErrorToClient( std::string path, header function_to_create_header)
{
	std::string		response = (*function_to_create_header)();
	aux_read_file	aux;

	aux.path = path;
	if (!getContentFile(aux))
		return (false);
	response += aux.content;
	if (send(_client_fd, response.c_str(), response.size(), 0) == -1)
		return (write_error("Error: Server::send_error_404: send"));
	return (true);
}

bool	Server::sendErrorResponseToClient( int status )
{
	std::cout << "Status: " << status << std::endl;
	if (status == ERROR404)
		sendErrorToClient("./error_pages/404_lufy_chorando.html", &create_header_404);
	else if (status == ERROR_INTERNAL)
		sendErrorToClient("./error_pages/500_internal_server.html", &create_header_500);
	else if (status == ERROR_BAD_REQUEST)
		sendErrorToClient("./error_pages/400_bad_request.html", &create_header_400);
	return (false);
}
