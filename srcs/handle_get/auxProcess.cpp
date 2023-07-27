/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxProcess.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:50:06 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	executeFork( ChildProcessData& infos)
{
	if (pipe(infos.fd) == -1)
		write_error("Server::handle_GET_requesition: pipe");
	infos.pid = fork();
	if (infos.pid == -1)
		write_error("Server::handle_GET_requesition: fork");
	return(true);
}
