/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 10:03:19 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

/*                                      server

sin_family: especifica a família do endereço, geralmente definido como AF_INET para endereços IPv4.

sin_port: especifica o número da porta em que o servidor está ouvindo as conexões de entrada.

sin_addr: especifica o endereço IP do servidor. Pode ser especificado como INADDR_ANY,
o que significa que o servidor aceitará conexões em qualquer endereço IP.

sin_zero: é um campo de preenchimento para garantir que a estrutura tenha o mesmo tamanho que a sockaddr,
usada para compatibilidade com sistemas mais antigos.Esse campo não é usado atualmente.     */

bool	Server::createSockeConfigured( int& serverFd )
{
	int	on = 1;

	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd == -1)
		return (writeStreerrorPrefix("Error: Not create socket"));
	if (set_fdNotBlock(serverFd) == false)
		return (writeStreerrorPrefix("Error: Not set socket non-blocking"));
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
		return (writeStreerrorPrefix("Error: Not set socket option"));
	return (true);
}

bool	Server::bind_socket( int& serverFd, Server_configuration* server)
{
	struct sockaddr_in port;

	port.sin_family = AF_INET;
	port.sin_addr.s_addr = INADDR_ANY;
	port.sin_port = htons(server->get_port());

	if (bind(serverFd, (struct sockaddr *)&port, sizeof(port)) >= 0)
		return (true);
	return (writeStreerrorPrefix("Error: Bind_socket"));
}

bool	Server::listen_socket( int& serverFd )
{
	if (listen(serverFd, MAX_CONNECTIONS) == 0)
		return (true);
	return (writeStreerrorPrefix("Error: Listen_socket"));
}

bool	Server::createServer( int& serverFd, Server_configuration* server)
{
	write_debug_prefix(AZUL, "\nCreating server...");
	if (createSockeConfigured(serverFd) == false)
		return (false);
	write_debug("Binding server...");
	if (bind_socket(serverFd, server) == false)
		return (write_error_prefixI("Port: ", server->get_port()));
	write_debug("Listening server...");
	if (listen_socket(serverFd) == false)
		return (false);
	return (true);
}
