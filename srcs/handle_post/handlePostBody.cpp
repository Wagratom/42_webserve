/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostBody.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 13:22:42 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::readAndSaveDatas(Response* response, std::vector<char>& buffer)
{
	response->bytesRead = read(_client_fd, buffer.data(), response->contentLenght);
	if (response->bytesRead == -1)
		return (writeStreerrorPrefix("Error: readAndSaveDatas"));
	response->totalBytesRead += response->bytesRead;
	if (response->totalBytesRead >= response->contentLenght)
		response->endProcess = true;
	return (true);
}

static bool	handleProcessResponse(Response* response, std::vector<char>& buffer)
{
	if (response->totalBytesRead == response->contentLenght)
	{
		response->endProcess = true;
		if (response->bytesRead != 0)
			write(response->fd[1], buffer.data(), response->bytesRead);
		close(response->fd[1]);
	}
	else
		write(response->fd[1], buffer.data(), response->bytesRead);
	return (true);
}

bool	Server::handlePostBody( void )
{
	Response*			response = _response[_client_fd];
	std::vector<char>	buffer(response->contentLenght);

	write_debug("handlePostBody");
	if (readAndSaveDatas(response, buffer) == false)
		return (false);
	if (response->hasProcess == false)
		return createProcessResponse(response, buffer);
	handleProcessResponse(response, buffer);
	if (response->endProcess)
		return (responseServer("200"));
	buffer.clear();
	return (true);
}
