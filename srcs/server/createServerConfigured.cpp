/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServerConfigured.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/19 21:43:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::create_server_aux(Server_configuration* server)
{
	int	serverFd;
	if (createServer(serverFd, server) == false)
		return (false);
	if (confServeToRead(serverFd) == false)
		return (false);
	write_debug_number("Port: ", (server)->get_port());
	write_debug_prefix("ServerName: ", (server)->get_server_name());
	_serversConf[(server)->get_port()] = server;
	_serversConf[serverFd] = server;
	return (true);
}

bool	Server::createServerConfigured( void )
{
	std::vector<Server_configuration*>	auxServer = server();
	bool								firstServer = true;

	write_debug("\033[0;36m\tCreating server configured");
	if (create_epoll() == false)
		return (false);
	for (std::vector<Server_configuration*>::iterator it = auxServer.begin(); it != auxServer.end(); it++)
	{
		if (create_server_aux(*it) == false && firstServer == true)
			return (false);
		firstServer = false;
	}
	return (true);
}
