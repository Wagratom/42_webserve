/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readRequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 12:58:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool static	Read_AppendBuffer(int& FD, std::string& buffer)
{
	char	tmp[10];
	int		bytesRead = 0;

	bytesRead = recv(FD, tmp, 10, 0);
	if (bytesRead == -1)
		return (writeStreerrorPrefix("Error: readRequest: "));
	tmp[bytesRead] = '\0';
	buffer.append(tmp, bytesRead);
	return true;
}

bool	Server::readHeaderRequest()
{
	if (Read_AppendBuffer(_client_fd, _response->buffer) == false)
		return (false);
	if (_response->buffer.find("\r\n\r\n") == std::string::npos)
		return (true);
	_response->endHeader = true;
	write_debug_prefix(CIANO, "\n\t Header received");
	write_debug_prefix(AZUL, _response->buffer);
	return (true);
}
