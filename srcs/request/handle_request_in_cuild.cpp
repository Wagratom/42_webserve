/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request_in_cuild.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/30 11:24:20 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	error_in_request(epoll_event& event)
{
	int	i = 0;
	while (i < 1025)
		close(i);
	close(event.data.fd);
	exit(EXIT_FAILURE);
}

bool	Server::configured_child(epoll_event& event)
{
	int	flags;

	flags = fcntl(event.data.fd, F_GETFL, 0); // pengando as propriedades do fd
	if (flags == -1)
		return (write_error_prefix("configured_child"));
	if (fcntl(event.data.fd, F_SETFL, flags | O_NONBLOCK) == -1) // setando o fd para nao bloquear
		return (write_error_prefix("configured_child"));
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, _server_fd, &event) == -1) // removendo o serve do epoll
		write_error_prefix("configured_child");
	close(_server_fd); // fechando o fd do server
	return (true);
}

void	reply_to_client(epoll_event& event)
{
	std::cout << "reply_to_client" << std::endl;
	std::string resposta = "HTTP/1.1 200 OK\r\n";
	resposta += "Content-Type: text/html\r\n\r\n";
	resposta += "<html><head><title>Exemplo</title></head><body><h1>Olá, mundo!</h1></body></html>";
	send(event.data.fd, resposta.c_str(), resposta.length(), 0);
}

/*############################################################################*/
/*                        Handle request in chuild                            */
/*############################################################################*/

void	Server::handle_request_in_child(epoll_event& event)
{
	std::cout << "handle_request_in_child" << std::endl;
	if (!configured_child(event))
		error_in_request(event);
	if (!control_chuild(event))
		error_in_request(event);
	exit(0);
}

bool	Server::control_chuild(epoll_event& event)
{
	std::string	buffer;

	while (true)
	{
		if (!read_request(buffer, event))
			return (false);
		if (!parse_request(buffer))
			return (false);
		if (response_request() == false)
			return (false);
		buffer.clear();
		sleep(100);
	}
	exit(0);
	return (true);
}
