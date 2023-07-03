/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxProcess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:50:06 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/02 18:45:49 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	executeFork( ChildProcessData& infos)
{
	if (pipe(infos.fd) == -1)
		write_error("Error: Server::handle_GET_requesition: pipe");
	infos.pid = fork();
	if (infos.pid == -1)
		write_error("Error: Server::handle_GET_requesition: fork");
	return(true);
}

// void	executeCGI(char** argv, char** envp)
// {
// 	execve("/usr/bin/php-cgi7.4", argv, envp);
// 	exit(ERROR500);
// }

