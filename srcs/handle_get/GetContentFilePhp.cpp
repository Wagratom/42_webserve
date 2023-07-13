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

	dup2(infos.fd[1], STDOUT_FILENO);
	close(infos.fd[0]);
	close(infos.fd[1]);
	execlp(scrptName, scrptName, NULL);
}

static bool	contentFilePHP(auxReadFiles& dst, ChildProcessData& infosProcess)
{
	char	buffer[1024];
	int		bytes_read;

	close(infosProcess.fd[1]);
	waitpid(infosProcess.pid, &infosProcess.status, 0);
	if (infosProcess.status != 0)
		return (write_error("contentFilePHP:: Error in callExecuteCgi"));
	while ((bytes_read = read(infosProcess.fd[0], buffer, 1024)) > 0)
		dst.content.append(buffer, bytes_read);
	close(infosProcess.fd[0]);
	return (true);
}

bool	getContentFilePHP(auxReadFiles& dst)
{
	ChildProcessData	infosProcess;

	write_debug("getContentFilePHP");
	write_debug_prefix("File: ", dst.path);
	if (executeFork(infosProcess) == false)
		return (false);
	if (infosProcess.pid == CHILD)
		callExecuteCgi(dst, infosProcess);
	return contentFilePHP(dst, infosProcess);
}
