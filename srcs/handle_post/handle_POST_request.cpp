/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/06 10:46:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_POST_requesition()
{
	std::string	contentLength = getenv("CONTENT_LENGTH");
	int			contentLenght = std::strtol(contentLength.c_str(), NULL, 10);

	std::cout << "handle_POST_requesition" << std::endl;
	if (server()->get_clientMaxBodySize() < contentLenght)
		return (responseClientError(ERROR413, getErrorPageMapServer("413")));
	if (_parserRequest->get_request()[0])
		return (responseClientError(ERROR400, getErrorPageMapServer("400")));
	if (redirectBodyCGI(contentLenght) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (responseServer("200"));
}

void static setenvs( void )
{
	setenv("REDIRECT_STATUS", "200", 1);
	setenv("SCRIPT_FILENAME", "./root/handlePOST.php", 1);
	setenv("PATH_DIR", PATH_UPLOAD, 1);
	setenv("DOCUMENT_ROOT", "/home/wallas/42_webserve/", 1);
}

void	Server::handleProcessPOST(ChildProcessData& auxProcess, std::vector<char>& content)
{
	if (auxProcess.pid == CHILD_PROCESS)
	{
		dup2(auxProcess.fd[0], STDIN_FILENO);
		close(auxProcess.fd[0]);
		close(auxProcess.fd[1]);
		close(_client_fd);
		execlp("./root/handlePOST.php", "./root/handlePOST.php", NULL);
		write_error(strerror(errno));
		exit(1);
	}
	if (auxProcess.pid != CHILD_PROCESS)
	{
		write(auxProcess.fd[1], content.data(), content.size());
		close(auxProcess.fd[0]);
		close(auxProcess.fd[1]);
	}
}

bool	Server::redirectBodyCGI( int& contentLenght )
{
	ChildProcessData	auxProcess;
	std::vector<char>	buffer(contentLenght);

	setenvs();
	if ((read(_client_fd, buffer.data(), contentLenght) == -1))
		return (write_error(strerror(errno)));
	if (executeFork(auxProcess) == false)
		return (write_error("redirectBodyCGI: executing fork"));
	handleProcessPOST(auxProcess, buffer);
	return true;
}
