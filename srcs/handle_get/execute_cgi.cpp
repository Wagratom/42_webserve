/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cgi.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:50:06 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/11 21:21:47 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	execute_fork( ChildProcessInfo& infos)
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
	std::cout << "execute_cgi_in_chuild" << std::endl;
	if (execute_fork(tools_chuild) == false)
		return (false);
	if (tools_chuild.pid == CHILD_PROCESS)
	{
		close(tools_chuild.fd[0]);
		dup2(tools_chuild.fd[1], STDOUT_FILENO);
		execute_cgi();
	}
	return (true);
}

void	Server::execute_cgi( void )
{
	char**		argv = new char*[3];
	std::string	path;

	if (!generete_path_to_response(path, server()->get_root(), server()->get_index()))
		exit(ERROR404);
	argv[0] = (char *)"/usr/bin/php-cgi";
	argv[1] = (char *)path.c_str();
	argv[2] = NULL;
	if (execve("/usr/bin/php-cgi7.4", argv, NULL) == -1)
		exit(ERROR_SERVE);
	exit(ERROR_SERVE);
}
