/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostBody.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 00:03:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

// bool	Server::readAndSaveBytes(Response* response, std::vector<char>& buffer)
// {
// 	response->bytesRead = read(_client_fd, buffer.data(), response->contentLenght);
// 	if (response->bytesRead == -1)
// 		return (write_error_prefix("handlePostBody"));
// 	response->totalBytesRead += response->bytesRead;
// 	return (true);
// }

bool	Server::handlePostBody( void )
{
	Response*			response = _response[_client_fd];
	std::vector<char>	buffer(response->contentLenght);

	write_debug("handlePostBody");
	response->bytesRead = read(_client_fd, buffer.data(), response->contentLenght);
	if (response->bytesRead == -1)
		return (write_error_prefix("handlePostBody"));
	response->totalBytesRead += response->bytesRead;
	if (response->totalBytesRead == response->contentLenght)
	{
		if (response->bytesRead != 0)
			write(response->fd[1], buffer.data(), response->bytesRead);
		close(response->fd[1]);
	}
	if (response->hasProcess == true)
		write(response->fd[1], buffer.data(), response->bytesRead);
	else
	{
		if (redirectBodyCGI(response, buffer) == false)
			return (false);
	}
	buffer.clear();
	return (true);
}
