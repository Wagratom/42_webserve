/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 10:08:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

/*                                      server

sin_family: especifica a família do endereço, geralmente definido como AF_INET para endereços IPv4.

sin_port: especifica o número da porta em que o servidor está ouvindo as conexões de entrada.

sin_addr: especifica o endereço IP do servidor. Pode ser especificado como INADDR_ANY,
o que significa que o servidor aceitará conexões em qualquer endereço IP.

sin_zero: é um campo de preenchimento para garantir que a estrutura tenha o mesmo tamanho que a sockaddr,
usada para compatibilidade com sistemas mais antigos.Esse campo não é usado atualmente.     */

bool	create_socket(int& socket_dst)
{
	socket_dst = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_dst != -1)
		return (true);
	printf("Could not create socket");
	return (false);
}

bool	bind_socket(int& socket_dst)
{
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	if (bind(socket_dst, (struct sockaddr *)&server, sizeof(server)) >= 0)
		return (true);
	printf("bind failed. Error");
	return (false);
}

bool	listen_socket(int& socket_dst)
{
	if (listen(socket_dst, 5) == 0)
		return (true);
	printf("listen failed. Error");
	return (false);
}

bool	create_server(int& socket_dst)
{
	if (!create_socket(socket_dst))
		return (false);
	if (!bind_socket(socket_dst))
		return (false);
	if (listen_socket(socket_dst))
		return (false);
	return (true);
}
