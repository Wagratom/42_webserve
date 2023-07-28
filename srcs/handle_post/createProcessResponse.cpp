/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createProcessResponse.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/28 13:37:42 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static void	redirectCGI( Response*& response )
{
	char*	script = getenv("SCRIPT_FILENAME");

	setenv("REDIRECT_STATUS", "200", 1);
	dup2(response->process.fd[0], STDIN_FILENO);
	dup2(response->process.fd[1], STDOUT_FILENO);
	close(response->process.fd[0]);
	close(response->process.fd[1]);
	execlp(script, script, NULL);
	writeStreerrorPrefix("Error: redirectCGI");
	sleep(2);
	if (errno == ENOENT)
		exit(ERROR404);
	if (errno == EACCES)
		exit(ERROR403);
	if (errno == EISDIR)
		exit(ERROR403);
	if (errno == ENOTDIR)
		exit(ERROR404);
	exit(1);
}

void	Server::handleProcessPOST( void )
{
	if (_response->process.pid == CHILD_PROCESS)
	{
		close(_client_fd);
		redirectCGI(_response);
	}
	// close(_response->process.fd[0]);
}

bool	Server::createProcessResponse( void )
{
	write_debug("createProcessResponse");
	if (executeFork(_response->process) == false)
		return false;
	handleProcessPOST();
	_response->hasProcess = true;
	return true;
}
