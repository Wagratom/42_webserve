/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleBodyPost.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 14:23:39 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handleBodyPost( void )
{
	Response*	response = _response[_client_fd];
	char*		initialPos = (response->content.data() + response->totalBytesRead);
	int			rest = response->contentLenght - response->totalBytesRead;
	int			bytesRead;

	write_debug("handleBodyPost");
	bytesRead = read(_client_fd, initialPos, rest);
	if (bytesRead == -1)
		return (write_error(strerror(errno)));
	response->totalBytesRead += bytesRead;
	if (response->totalBytesRead < response->contentLenght)
		return (true);
	if (redirectBodyCGI() == false)
		return (false);
	bool	status = responseServer("200");
	response->content.clear();
	cleanupFd(_client_fd);
	return (status);
}
