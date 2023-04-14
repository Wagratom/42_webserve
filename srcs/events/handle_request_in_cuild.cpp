/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request_in_cuild.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:14:55 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

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

void	Server::handle_request_in_cuild(epoll_event& event)
{
	std::cout << "handle_request_in_cuild" << std::endl;
	std::string buffer;
	close(server_fd);
	if (!conf_fd_to_not_block(event))
		exit(EXIT_FAILURE);
	if (!read_request(buffer, event))
		exit(EXIT_FAILURE);
	std::cout << "buffer: " << buffer << std::endl;
	write(event.data.fd, "Accept\n", 7);
	close(event.data.fd);
	std::cout << "sai do filho" << std::endl;
	exit(0);
}
