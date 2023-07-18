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

// static bool	CheckAndSaveContentScript(auxReadFiles& dst, ChildProcessData& infosProcess)
// {
// 	char	buffer[1024];
// 	int		bytes_read;

// 	close(infosProcess.fd[1]);
// 	waitpid(infosProcess.pid, &infosProcess.status, 0);
// 	if (infosProcess.status != 0)
// 		return (write_error("contentFilePHP:: Error in callExecuteCgi"));
// 	while ((bytes_read = read(infosProcess.fd[0], buffer, 1024)) > 0)
// 		dst.content.append(buffer, bytes_read);
// 	close(infosProcess.fd[0]);
// 	return (true);
// }

static bool	checkAcess(std::string path, auxReadFiles& dst)
{
	if (access(path.c_str(), R_OK) == 0)
		return (true);
	dst.notPermmision = true;
	return (writeStreerrorPrefix("Error: getContentFilePHP: "));
}

bool	getContentFilePHP(auxReadFiles& dst)
{
	write_debug("getContentFilePHP");
	write_debug_prefix("File: ", dst.path);
	if (checkAcess(dst.path, dst) == false)
		throw std::exception();
	ChildProcessData	auxProcess;
	bzero(&auxProcess, sizeof(ChildProcessData));
	if (executeFork(auxProcess) == false)
		throw std::exception();
	if (auxProcess.pid == CHILD)
		callExecuteCgi(dst, auxProcess);
	close(auxProcess.fd[1]);
	if (readOuputFormatedCGI(auxProcess, dst.content) == false)
		throw std::exception();
	return (true);

}
