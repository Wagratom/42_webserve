/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleProcessPOST.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/11 23:22:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void static setenvs( void )
{
	setenv("REDIRECT_STATUS", "200", 1);
	setenv("SCRIPT_FILENAME", "./root/handlePOST.php", 1);
	setenv("PATH_DIR", PATH_UPLOAD, 1);
	setenv("DOCUMENT_ROOT", "/home/wallas/42_webserve/", 1);
}

static void	redirectCGI( Response* response )
{
	dup2(response->fd[0], STDIN_FILENO);
	close(response->fd[0]);
	close(response->fd[1]);

	execlp("./root/handlePOST.php", "./root/handlePOST.php", NULL);
	write_error(strerror(errno));
	exit(1);
}

void	Server::handleProcessPOST(Response* response, std::vector<char>& buffer)
{
	if (response->pid == CHILD_PROCESS)
	{
		close(_client_fd);
		redirectCGI(response);
	}
	std::cout << "content lenght: " << getenv("CONTENT_LENGTH") << std::endl;
	std::cout << "Content bytesRead" << response->bytesRead << std::endl;
	write(response->fd[1], buffer.data(), response->bytesRead);
	close(response->fd[0]);
}

bool	Server::redirectBodyCGI(Response* response, std::vector<char>& buffer)
{
	setenvs();
	std::cout << "redirectBodyCGI" << std::endl;
	if (pipe(response->fd) == -1)
		return (write_error("redirectBodyCGI: creating pipe"));
	response->pid = fork();
	if (response->pid == -1)
		return (write_error("redirectBodyCGI: executing fork"));
	handleProcessPOST(response, buffer);
	response->hasProcess = true;
	return true;
}
