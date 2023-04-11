/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 13:35:11 by wwallas-         ###   ########.fr       */
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
	std::cout << "Error: an epoll_create()" << std::endl;
	return (false);
}

bool	add_serve_in_mode_read(int&socket_fd, int& epoll_fd)
{
	struct epoll_event event;

	event = (epoll_event) {0};
	event.data.fd = socket_fd;
	event.events = EPOLLIN;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) != -1)
		return (true);
	std::cout << "Error: an epoll_ctl()" << std::endl;
	return (false);
}

bool	conf_serve_to_read(int& socket_fd, int& epoll_fd)
{
	if (!create_epoll(epoll_fd))
		return (false);
	if (!add_serve_mode_read(socket_fd, epoll_fd))
		return (false);
}

int main( void )
{
	int socket_fd;
	int	epoll_fd;

	if (create_server(socket_fd))
		return (1);
	if (conf_serve_to_read(socket_fd, epoll_fd))
		return (1);
	return(0)

}


