/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServerConfigured.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/30 13:47:21 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static void addedServenameInHost(std::string serveName)
{
	std::string host = "127.0.0.1 " + serveName;
	std::ofstream file("/etc/hosts", std::ios::app);  // Abre o arquivo em modo de apêndice

	if (!file.is_open())
		std::cout << "\033[0;31m\tError: File /etc/hosts not open" << std::endl;
	else
		file << host << std::endl;
	file.close();
}

bool	Server::createServerConfigured( void )
{
	std::vector<Server_configuration*>	auxServer = server();
	bool								hasServerValid = false;
	int									serverFd;

	write_debug("\033[0;36m\tCreating server configured");
	if (create_epoll() == false)
		return (false);
	for (std::vector<Server_configuration*>::iterator it = auxServer.begin(); it != auxServer.end(); it++)
	{
		if (createServer(serverFd, (*it)))
		{
			hasServerValid = true;
			_serversConf[(*it)->get_port()] = (*it);
			_serversConf[serverFd] = (*it);
			addedServenameInHost((*it)->get_server_name());
			std::cout << (*it)->get_server_name() << std::endl;
		}
	}
	if (hasServerValid == false)
		return (write_error("\033[0;31m\tError: No server valid"));
	return (true);
}
