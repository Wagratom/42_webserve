/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 14:34:58 by wwallas-         ###   ########.fr       */
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

bool	Server::createSockeConfigured( void )
{
	int	on = 1;

	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd == -1)
		return (write_error_prefix("Error: Not create socket"));
	if (set_fdNotBlock(_server_fd) == false)
		return (write_error_prefix("Error: Not set socket non-blocking"));
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
		return (write_error_prefix("Error: Not set socket option"));
	return (true);
}

bool	Server::bind_socket( void )
{
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(_parserFile->get_server_configuration()->get_port());

	if (bind(_server_fd, (struct sockaddr *)&server, sizeof(server)) >= 0)
		return (true);
	return (write_error_prefix("Error: Bind_socket"));
}

bool	Server::listen_socket( void )
{
	if (listen(_server_fd, MAX_CONNECTIONS) == 0)
		return (true);
	return (write_error_prefix("Error: Listen_socket"));
}

bool	Server::create_server( void )
{
	write_debug("Creating server...");
	if (createSockeConfigured() == false)
		return (false);
	write_debug("Binding server...");
	if (bind_socket() == false)
		return (false);
	write_debug("Listening server...");
	if (listen_socket() == false)
		return (false);
	return (true);
}
