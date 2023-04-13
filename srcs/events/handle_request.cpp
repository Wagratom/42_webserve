/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:23:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 23:00:49 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	conf_fd_to_not_block(epoll_event* event)
{
	int	flags;

	flags = fcntl(event[0].data.fd, F_GETFL, 0); // pengando as propriedades do fd
	if (flags == -1)
		return (write_error_prefix("conf_fd_to_not_block"));
	if (fcntl(event[0].data.fd, F_SETFL, flags | O_NONBLOCK) == -1) // setando o fd para nao bloquear
		return (write_error_prefix("conf_fd_to_not_block"));
	return (true);
}

bool	verift_error(int bytes_read)
{
	if (bytes_read != -1)
		return (false);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (false);
	return (true);
}

bool	read_request(std::string& buffer, epoll_event* event)
{
	char	tmp[1024];
	int		bytes_read;

	while (true)
	{
		bytes_read = recv(event[0].data.fd, tmp, 1, 0);
		if (verift_error(bytes_read))
			return (write_error_prefix("read_request"));
		if (bytes_read == 0 || bytes_read == -1)
			break ;
		buffer.append((char*)tmp, bytes_read);
	}
	return (true);
}

bool	handle_request(epoll_event* event)
{
	std::string buffer;

	std::cout << "handle_request" << std::endl;
	if (!conf_fd_to_not_block(event))
		return (false);
	if (!read_request(buffer, event))
		return (false);
	std::cout << "vou escrever no fd" << std::endl;
	write(event[0].data.fd, "Accept\n", 7);
	close(event->data.fd);
	return (true);
}
