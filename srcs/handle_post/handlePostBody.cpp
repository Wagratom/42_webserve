/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePostBody.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/24 09:16:56 by wwallas-         ###   ########.fr       */
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

bool	Server::readAndSaveDatas(Response*& response, std::vector<char>& buffer)
{
	response->bytesRead = read(_client_fd, buffer.data(), response->contentLenght);
	if (response->bytesRead == -1)
		return (writeStreerrorPrefix("Error: readAndSaveDatas"));
	response->totalBytesRead += response->bytesRead;
	return (true);
}

bool	Server::handleProcessResponse(Response*& response, std::vector<char>& buffer)
{
	int	status;

	write_debug("handleProcessResponse");
	write(response->process.fd[1], buffer.data(), response->bytesRead);
	if (response->totalBytesRead == response->contentLenght)
	{
		write_debug("Is end of body");
		close(response->process.fd[1]);
		if (waitpid(response->process.pid, &status, WNOHANG) == 0)
			return true;
		int	wexitstatus = checkStatusCGI(status);
		if (wexitstatus != 0)
			return responseClientError(wexitstatus, _serverUsing->get_root(), getErrorPageMap(_errorMapUsing, get_stringError(wexitstatus)));
		responseServer();
		cleanupResponse(_client_fd);
		return (handleKeepAlive());
	}
	return (true);
}

bool	Server::handlePostBody( void )
{
	Response*			response = _responses.find(_client_fd)->second;
	std::vector<char>	buffer(response->contentLenght);

	write_debug("handlePostBody");
	if (readAndSaveDatas(response, buffer) == false)
		return (false);
	if (response->hasProcess == false)
		createProcessResponse(response);
	return (handleProcessResponse(response, buffer));
}
