/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cgi.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:50:06 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/14 13:13:37 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	execute_fork( ChildProcessInfo& infos)
{
	if (pipe(infos.fd) == -1)
		write_error("Error: Server::handle_GET_requesition: pipe");
	infos.pid = fork();
	if (infos.pid == -1)
		write_error("Error: Server::handle_GET_requesition: fork");
	return(true);
}

bool	Server::execute_cgi_in_chuild( ChildProcessInfo& tools_chuild )
{
	std::string	path;
	char	*argv[3];
	if (execute_fork(tools_chuild) == false)
		return (false);
	if (tools_chuild.pid == CHILD_PROCESS)
	{
		if (!generete_path_to_response(path, server()->get_root(), server()->get_index()))
			exit(ERROR404);

		argv[0] = (char *)"/usr/bin/php-cgi";
		argv[1] = (char *)path.c_str();
		argv[2] = NULL;

		dup2(tools_chuild.fd[1], STDOUT_FILENO);
		close(tools_chuild.fd[0]);
		close(tools_chuild.fd[1]);
		execute_cgi(argv, NULL);
	}
	return (true);
}

void	execute_cgi(char** argv, char** envp)
{
	execve("/usr/bin/php-cgi7.4", argv, envp);
	exit(ERROR_SERVE);
}
