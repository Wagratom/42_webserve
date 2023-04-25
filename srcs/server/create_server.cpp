/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:15:36 by wwallas-         ###   ########.fr       */
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

bool	Server::create_socket( void )
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd != -1)
		return (true);
	return (write_error_prefix("Create_socket"));
}

bool	Server::bind_socket( void )
{
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) >= 0)
		return (true);
	return (write_error_prefix("Bind_socket"));
}

bool	Server::listen_socket( void )
{
	if (listen(server_fd, MAX_CONNECTIONS) == 0)
		return (true);
	return (write_error_prefix("Listen_socket"));
}

bool	Server::create_server( void )
{
	if (!create_socket())
		return (false);
	if (!bind_socket())
		return (false);
	if (!listen_socket())
		return (false);
	return (true);
}
