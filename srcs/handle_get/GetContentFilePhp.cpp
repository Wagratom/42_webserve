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
	char*	argv[3];

	argv[0] = (char *)"/usr/bin/php-cgi7.4";
	argv[1] = (char *)dst.path.c_str();
	argv[2] = NULL;
	dup2(infos.fd[1], STDOUT_FILENO);
	close(infos.fd[0]);
	close(infos.fd[1]);
	executeCGI(argv, NULL);
}

static bool	contentFilePHP(auxReadFiles& dst, ChildProcessData& infos)
{
	int		status;
	char	buffer[1024];
	int		bytes_read;

	close(infos.fd[1]);
	waitpid(infos.pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		return (write_error("Error: Server::handle_GET_requesition: php-cgi7.4"));
	while ((bytes_read = read(infos.fd[0], buffer, 1024)) > 0)
		dst.content.append(buffer, bytes_read);
	close(infos.fd[0]);
	return (true);
}

bool	getContentFilePHP(auxReadFiles& dst)
{
	ChildProcessData	infos;

	std::cout << "getContentFilePHP" << std::endl;
	if (executeFork(infos) == false)
		return (false);
	if (infos.pid == CHILD)
		callExecuteCgi(dst, infos);
	return contentFilePHP(dst, infos);
}
