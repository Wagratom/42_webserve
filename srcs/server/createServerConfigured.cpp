/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServerConfigured.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/10 21:35:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createServerConfigured( void )
{
	std::vector<Server_configuration*>	auxServer = server();

	write_debug("\033[0;36m\tCreating server configured");
	if (create_epoll() == false)
		return (false);
	for (std::vector<Server_configuration*>::iterator it = auxServer.begin(); it != auxServer.end(); it++)
	{
		int	serverFd;
		write_debug("\033[0;34m");
		if (create_server(serverFd, *it) == false)
			return (false);
		if (conf_serve_to_read(serverFd) == false)
			return (false);
		write_debug_number("Port: ", (*it)->get_port());
		write_debug_prefix("ServerName: ", (*it)->get_server_name());
		write_debug("\033[32mOk \n\n");
		_serversConf[(*it)->get_port()] = *it;
		_serversConf[serverFd] = *it;
	}
	write_debug("\033[0m");
	return (true);
}
