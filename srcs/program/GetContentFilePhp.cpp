/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseLocation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static void	callExecuteCgi(auxReadFiles& dst, ChildProcessData& infos)
{
	char*	scrptName = (char *)dst.path.c_str();

	setenv("REDIRECT_STATUS", "200", 1);
	setenv("SCRIPT_FILENAME", scrptName, 1);
	dup2(infos.fd[1], STDOUT_FILENO);
	close(infos.fd[0]);
	close(infos.fd[1]);
	execlp(scrptName, scrptName, NULL);
	writeStreerrorPrefix("Error: callExecuteCgi: ");
	exit(1);
}

static bool	checkAcess(std::string path, auxReadFiles& dst)
{
	if (access(path.c_str(), R_OK) == 0)
		return (true);
	dst.notPermmision = true;
	return (writeStreerrorPrefix("Error: getContentFilePHP: "));
}

bool	Server::getContentFilePHP(auxReadFiles& dst)
{
	write_debug("getContentFilePHP");
	if (checkAcess(dst.path, dst) == false)
		throw std::exception();
	if (createNewResponses(0) == false)
		return (false);
	dst.hasProcess = true;
	ChildProcessData& auxProcess = _responses.at(_client_fd)->process;
	if (executeFork(auxProcess) == false)
		throw std::exception();
	if (auxProcess.pid == CHILD_PROCESS)
		callExecuteCgi(dst, auxProcess);
	close(auxProcess.fd[1]);
	if (waitpid(auxProcess.pid, &auxProcess.status, WNOHANG) == 0)
		return true;
	dst.hasProcess = false;
	if (readOuputFormatedCGI(dst.content, auxProcess) == false)
		throw std::exception();
	cleanupResponse(_client_fd);
	return (true);

}
