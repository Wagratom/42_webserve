/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServerConfigured.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/10 11:23:17 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createServerConfigured( void )
{
	std::vector<Server_configuration*>	auxServer = server();
	int									serverFd;

	write_debug("\033[0;36m\tCreating server configured");
	for (std::vector<Server_configuration*>::iterator it = auxServer.begin(); it != auxServer.end(); it++)
	{
		write_debug("\033[0;34m");
		if (create_server(serverFd, *it) == false)
			return (false);
		if (conf_serve_to_read(serverFd) == false)
			return (false);
		write_debug_number("Port: ", (*it)->get_port());
		write_debug_prefix("ServerName: ", (*it)->get_server_name());
		write_debug("\033[32mOk \n\n");
		_servers_fd[serverFd] = *it;
	}
	write_debug("\033[0m");
	return (true);
}
