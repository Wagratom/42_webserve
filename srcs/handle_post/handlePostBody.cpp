/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostBody.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/13 14:37:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::readAndSaveDatas(Response*& response, std::vector<char>& buffer)
{
	response->bytesRead = read(_client_fd, buffer.data(), response->contentLenght);
	if (response->bytesRead == -1)
		return (writeStreerrorPrefix("Error: readAndSaveDatas"));
	response->totalBytesRead += response->bytesRead;
	if (response->totalBytesRead >= response->contentLenght)
		response->endProcess = true;
	return (true);
}

static void	handleProcessResponse(Response*& response, std::vector<char>& buffer)
{
	if (response->totalBytesRead == response->contentLenght)
	{
		response->endProcess = true;
		if (response->bytesRead != 0)
			write(response->fd[1], buffer.data(), response->bytesRead);
		close(response->fd[1]);
		return ;
	}
	write(response->fd[1], buffer.data(), response->bytesRead);
}

bool	Server::handlePostBody( void )
{
	Response*			response = _responses.find(_client_fd)->second;
	std::vector<char>	buffer(response->contentLenght);

	write_debug("handlePostBody");
	if (readAndSaveDatas(response, buffer) == false)
		return (false);
	if (response->hasProcess == false)
		return createProcessResponse(response, buffer);
	handleProcessResponse(response, buffer);
	if (response->endProcess == false)
		return (true);
	_write = response->write;
	if (responseServer("200") == false)
		return (false);
	return (handleKeepAlive());
}
