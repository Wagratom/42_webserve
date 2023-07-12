/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientError.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:52:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 09:29:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendErrorToClient( std::string path, std::string error)
{
	auxReadFiles	tmp;
	std::string		header;

	std::cout << "sendErrorToClient" << std::endl;
	tmp.path = path;
	if (getContentFile(tmp) == false)
		return (false);
	header = generateHeaderDynamicStatus(tmp, error);
	header += tmp.content + "\r\n";
	return sendResponseClient(header);
}

bool	Server::responseClientError( int status, std::string pathFileError )
{
	std::cout << "responseClientError: " << status << std::endl;
	if (pathFileError.empty())
		pathFileError = _defaultErrorPage[status];
	if (status == ERROR404)
		return sendErrorToClient(pathFileError, "404 Not Found");
	else if (status == ERROR500)
		return sendErrorToClient(pathFileError, "500 Internal Server Error");
	else if (status == ERROR400)
		return sendErrorToClient("./error_pages/400_bad_request.html", "400 Bad Request");
	else if (status == ERROR415)
		// enviar um error de formato do payload não é um formato suportado.
		return (false);
	else if (status == ERROR413)
		return sendErrorToClient(pathFileError, "413 Payload Too Large");
	return (true);
}
