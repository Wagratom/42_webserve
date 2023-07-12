/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientGET.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 09:32:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static void	callCGI(ChildProcessData& auxProcess)
{
	char*		script = getenv("SCRIPT_FILENAME");

	dup2(auxProcess.fd[1], STDOUT_FILENO);
	close(auxProcess.fd[0]);
	close(auxProcess.fd[1]);
	execlp(script, script, NULL);
	std::cerr << strerror(errno) << std::endl;
	exit(ERROR500);
}

static void	setEnvs(std::string endPoint)
{
	size_t			questionMarkPos = endPoint.find("?");
	std::string		scriptHandler	= "." + endPoint.substr(0, questionMarkPos);
	std::string		query_string	= endPoint.substr(questionMarkPos + 1);

	setenv("QUERY_STRING", query_string.c_str(), 1);
	setenv("SCRIPT_FILENAME", scriptHandler.c_str(), 1);
	setenv("SCRIPT_NAME", PATH_CGI, 1);
	setenv("REDIRECT_STATUS", "200", 1);
}

bool	Server::responseInputGET(std::string endPoint)
{
	ChildProcessData	auxProcess;
	std::string			content;

	setEnvs(endPoint);
	if (executeFork(auxProcess) == false)
		return (write_error("Error: Server::responseInputGET: executeFork"));
	if (auxProcess.pid == CHILD_PROCESS)
		callCGI(auxProcess);
	waitpid(auxProcess.pid, &auxProcess.status, 0);
	if (auxProcess.status != 0)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	if (readOuputFormatedCGI(auxProcess, content) == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (sendResponseClient(content));
}
