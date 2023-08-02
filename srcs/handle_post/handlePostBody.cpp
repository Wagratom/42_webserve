/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostBody.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/01 20:44:48 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

int	checkStatusCGI(int& status)
{
	if (status == 0)
		return 0;
	write_error("handleProcessResponse: CGI error");
	return (WEXITSTATUS(status));
}

bool	Server::readAndSaveDatas()
{
	char	buffer[_response->contentLenght + 1];

	write_debug("Read body post");
	_response->bytesRead = read(_client_fd, buffer, _response->contentLenght);
	if (_response->bytesRead == -1)
		return (writeStreerrorPrefix("Error: readAndSaveDatas"));
	buffer[_response->bytesRead] = '\0';
	_response->buffer.append(buffer, _response->bytesRead);
	_response->sizeContent += _response->bytesRead;

	return (true);
}

bool	Server::handleProcessResponse( void )
{
	int		status;

	write_debug("handleProcessResponse");
	write(_response->process.fd[1], _response->buffer.data(), _response->bytesRead);
	_response->buffer.clear();
	if (_response->sizeContent == _response->contentLenght)
	{
		write_debug("Is end Post\n");
		close(_response->process.fd[1]);
		if (waitpid(_response->process.pid, &status, WNOHANG) == 0)
			return true;
		_response->hasProcess = false;
		int	wexitstatus = checkStatusCGI(status);
		if (wexitstatus != 0)
			return responseClientError(wexitstatus, _response->root, getErrorPageMap(_response->errorPage, get_stringError(wexitstatus)));
		if (responseServer() == false)
			return (responseClientError(ERROR500, _response->root, getErrorPageMap(_response->errorPage, "500")));

		return (handleKeepAlive());
	}
	return (true);
}

bool	Server::handlePostBody( void )
{
	write_debug("handlePostBody");
	if (_response->hasProcess == false)
		createProcessResponse();
	if (_response->buffer.empty() == false)
		return (handleProcessResponse());
	if (readAndSaveDatas() == false)
		return (false);
	return (handleProcessResponse());

}
