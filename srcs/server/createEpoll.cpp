/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createEpoll.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/10 11:47:47 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

/*
EPOLLIN - indica que há dados para serem lidos no descritor de arquivo.
EPOLLOUT - indica que é possível escrever dados no descritor de arquivo sem bloqueio.
EPOLLERR - indica que ocorreu um erro no descritor de arquivo.
EPOLLHUP - indica que o descritor de arquivo foi fechado
EPOLLRDHUP: Evento que indica que a outra ponta da conexão TCP fechou a conexão ou desapareceu. É semelhante ao EPOLLHUP, mas específico para conexões TCP.

Edge-triggered mode (EPOLLET) - sinaliza um evento apenas quando ocorre uma mudança de estado, como a chegada de novos dados.
Level-triggered mode (default) - sinaliza um evento enquanto o estado for verdadeiro, como a presença de dados para leitura.
*/

bool	Server::create_epoll( void )
{
	_epoll_fd = epoll_create(5);
	if (_epoll_fd == -1)
		return (write_error_prefix("Create_epoll"));
	write_debug("Creating epoll...");
	return (true);
}