/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 22:15:17 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	error_in_request(epoll_event& event)
{
	close(event.data.fd);
	exit(EXIT_FAILURE);
}

bool	Server::conf_fd_to_not_block(epoll_event& event)
{
	int	flags;

	flags = fcntl(event.data.fd, F_GETFL, 0); // pengando as propriedades do fd
	if (flags == -1)
		return (write_error_prefix("conf_fd_to_not_block"));
	if (fcntl(event.data.fd, F_SETFL, flags | O_NONBLOCK) == -1) // setando o fd para nao bloquear
		return (write_error_prefix("conf_fd_to_not_block"));
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

bool	Server::handle_request(epoll_event& event)
{
	std::string	buffer;

	while (true)
	{
		if (!read_request(buffer, event))
			return (false);
		if (buffer == "quit")
			return (true);
		if (!parse_request(buffer))
			return (false);
		buffer.clear();
	}
	return (true);
}

void	Server::handle_request_in_child(epoll_event& event)
{
	write(event.data.fd, "Accept\n", 7);
	close(server_fd);
	if (!conf_fd_to_not_block(event))
		error_in_request(event);

	// std::string resposta = "HTTP/1.1 200 OK\r\n";
	// resposta += "Content-Type: text/html\r\n\r\n";
	// resposta += "<html><head><title>Exemplo</title></head><body><h1>Olá, mundo!</h1></body></html>";
	// send(event.data.fd, resposta.c_str(), resposta.length(), 0);

	if (!handle_request(event))
		error_in_request(event);
	exit(0);
}

do pai
cleanup();

do filho
