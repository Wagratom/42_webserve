/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/16 17:12:05 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	error_in_request(epoll_event& event)
{
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
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, server_fd, &event) == -1) // removendo o serve do epoll
		write_error_prefix("configured_child");
	close(server_fd); // fechando o fd do server
	return (true);
}

bool	Server::verift_error(int bytes_read)
{
	if (bytes_read != -1)
		return (false);
	if (errno == EAGAIN || errno == EWOULDBLOCK) // Erros for not data to read // valid error
		return (false);
	return (true);
}

bool	Server::read_request(std::string& buffer, epoll_event& event)
{
	char	tmp[1024];
	int		bytes_read;

	while (true)
	{
		bytes_read = recv(event.data.fd, tmp, 1, 0);
		if (verift_error(bytes_read))
			return (write_error_prefix("read_request"));
		if (bytes_read == 0 || bytes_read == -1)
			break ;
		buffer.append((char*)tmp, bytes_read);
	}
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

bool	Server::handle_request(epoll_event& event)
{
	std::string	buffer;

	reply_to_client(event);
	while (true)
	{
		if (!read_request(buffer, event))
			return (false);
		if (!parse_request(buffer))
			return (false);
		buffer.clear();
	}
	exit (0);
	return (true);
}

void	Server::handle_request_in_child(epoll_event& event)
{
	std::cout << "handle_request_in_child" << std::endl;
	if (!configured_child(event))
		error_in_request(event);
	if (!handle_request(event))
		error_in_request(event);
	exit(0);
}

server
{}
