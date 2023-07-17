/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientListFiles.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 19:01:02 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

// static void	callCGI(ChildProcessData& auxProcess)
// {
// 	char*		script = getenv("SCRIPT_FILENAME");

// 	dup2(auxProcess.fd[1], STDOUT_FILENO);
// 	close(auxProcess.fd[0]);
// 	close(auxProcess.fd[1]);
// 	execlp(script, script, NULL);
// 	std::cerr << strerror(errno) << std::endl;
// 	exit(ERROR500);
// }

// static void	setenvs(std::string pathDir, std::string script)
// {
// 	setenv("SCRIPT_FILENAME", script.c_str(), 1);
// 	setenv("SCRIPT_NAME", " /usr/bin/php-cgi", 1);
// 	setenv("PATHDIR", pathDir.c_str(), 1);
// 	setenv("REDIRECT_STATUS", "200", 1);
// 	setenv("SERVER_SOFTWARE", "TDD/4.0", 1);
// 	setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
// }

// bool	Server::responseClientListFiles( std::string pathDir, std::string script)
// {
// 	std::ostringstream	oss;
// 	ChildProcessData	auxProcess;
// 	std::string			content;

// 	write_debug("responseClientListFiles");
// 	setenvs(pathDir, script);
// 	if (executeFork(auxProcess) == false)
// 		return (responseClientError(ERROR500, _serversConf[_port]->get_root(), getErrorPageMapServer("500")));
// 	if (auxProcess.pid == CHILD_PROCESS)
// 		callCGI(auxProcess);
// 	waitpid(auxProcess.pid, &auxProcess.status, 0);
// 	if (auxProcess.status != 0)
// 		return (responseClientError(ERROR500, _serversConf[_port]->get_root(), getErrorPageMapServer("500")));
// 	close(auxProcess.fd[1]);
// 	if (readOuputFormatedCGI(auxProcess, content) == false)
// 		return (responseClientError(ERROR500, _serversConf[_port]->get_root(), getErrorPageMapServer("500")));
// 	return (sendResponseClient(content));
// }
