/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 11:46:31 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

/*
EPOLLIN - indica que há dados para serem lidos no descritor de arquivo.
EPOLLOUT - indica que é possível escrever dados no descritor de arquivo sem bloqueio.
EPOLLERR - indica que ocorreu um erro no descritor de arquivo.
EPOLLHUP - indica que o descritor de arquivo foi fechado

Edge-triggered mode (EPOLLET) - sinaliza um evento apenas quando ocorre uma mudança de estado, como a chegada de novos dados.
Level-triggered mode (default) - sinaliza um evento enquanto o estado for verdadeiro, como a presença de dados para leitura.
*/
bool	create_epoll(int& epoll_fd)
{
	epoll_fd = epoll_create(5);
	if (epoll_fd != -1)
		return (true);
	std::cout << "Error: an epoll_create()" << std::endl;
	return (false);
}

bool	create_epoll_configured(int& socket_fd, int& epoll_fd)
{
	if (create_epoll(epoll_fd))
		return (false);
	struct epoll_event event;
	event.data.fd = socket_fd;
	event.events = EPOLLIN;
}

int main( void )
{
	int socket_fd;
	int	epoll_fd;

	if (create_server(socket_fd))
		return (1);
	if (create_epoll_configured(socket_fd, epoll_fd))
		return (1);
	return(0)

}


