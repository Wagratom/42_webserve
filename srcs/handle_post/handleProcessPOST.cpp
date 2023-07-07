/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleProcessPOST.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 09:47:15 by wwallas-         ###   ########.fr       */
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

static void	redirectCGI( ChildProcessData auxProcess )
{
	dup2(auxProcess.fd[0], STDIN_FILENO);
	close(auxProcess.fd[0]);
	close(auxProcess.fd[1]);

	execlp("./root/handlePOST.php", "./root/handlePOST.php", NULL);
	write_error(strerror(errno));
	exit(1);
}

void	Server::handleProcessPOST(ChildProcessData& auxProcess, std::vector<char>& content)
{
	if (auxProcess.pid == CHILD_PROCESS)
	{
		close(_client_fd);
		redirectCGI(auxProcess);
	}
	write(auxProcess.fd[1], content.data(), content.size());
	close(auxProcess.fd[0]);
	close(auxProcess.fd[1]);
}

bool	Server::redirectBodyCGI( int& contentLenght )
{
	ChildProcessData	auxProcess;
	std::vector<char>	buffer(contentLenght);

	setenvs();
	if ((read(_client_fd, buffer.data(), contentLenght) == -1))
		return (write_error(strerror(errno)));
	write(1, buffer.data(), contentLenght);
	if (executeFork(auxProcess) == false)
		return (write_error("redirectBodyCGI: executing fork"));
	handleProcessPOST(auxProcess, buffer);
	return true;
}
