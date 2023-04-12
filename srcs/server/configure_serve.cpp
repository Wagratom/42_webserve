/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_serve.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 22:27:49 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

/*
EPOLLIN - indica que há dados para serem lidos no descritor de arquivo.
EPOLLOUT - indica que é possível escrever dados no descritor de arquivo sem bloqueio.
EPOLLERR - indica que ocorreu um erro no descritor de arquivo.
EPOLLHUP - indica que o descritor de arquivo foi fechado
EPOLLRDHUP: Evento que indica que a outra ponta da conexão TCP fechou a conexão ou desapareceu. É semelhante ao EPOLLHUP, mas específico para conexões TCP.

Edge-triggered mode (EPOLLET) - sinaliza um evento apenas quando ocorre uma mudança de estado, como a chegada de novos dados.
Level-triggered mode (default) - sinaliza um evento enquanto o estado for verdadeiro, como a presença de dados para leitura.
*/
bool	create_epoll(int& epoll_fd)
{
	epoll_fd = epoll_create(5);
	if (epoll_fd != -1)
		return (true);
	return (write_error_prefix("Create_epoll"));
}

bool	add_mode_read(int&socket_fd, int& epoll_fd)
{
	struct epoll_event event;

	memset(&event, 0, sizeof(event));
	event.data.fd = socket_fd;
	event.events = EPOLLIN;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) != -1)
		return (true);
	return (write_error_prefix("Add_mod_read"));
}

bool	conf_serve_to_read(server& data)
{
	if (!create_epoll(data.epoll_fd))
		return (false);
	if (!add_mode_read(data.socket_fd, data.epoll_fd))
		return (false);
	return (true);
}
