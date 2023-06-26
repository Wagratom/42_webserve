/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientError.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 12:20:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendErrorToClient( std::string path, std::string header)
{
	auxReadFiles	aux;

	aux.path = path;
	if (!getContentFile(aux))
		return (false);
	header += aux.content;
	if (send(_client_fd, header.c_str(), header.size(), 0) == -1)
		return (write_error("Error: Server::send_error_404: send"));
	return (true);
}

bool	Server::responseClientError( int status, std::string pathFileError )
{
	std::cout << "responseClientError" << std::endl;
	if (pathFileError.empty())
		pathFileError = "./error_pages/404_lufy_pensativo.html";
	std::cout << "pathFileError: " << pathFileError << std::endl;
	if (status == ERROR404)
		sendErrorToClient(pathFileError, generateHeaderDynamicStatus("404 Not Found"));
	else if (status == ERROR_INTERNAL)
		sendErrorToClient(pathFileError, generateHeaderDynamicStatus("500 Internal Server Error"));
	else if (status == ERROR_BAD_REQUEST)
		sendErrorToClient("./error_pages/400_bad_request.html", generateHeaderDynamicStatus("400 Bad Request"));
	else if (status == ERROR415)
		// enviar um error de formato do payload não é um formato suportado.
		return (false);
	return (true);
}
