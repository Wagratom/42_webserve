/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 21:15:48 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool	verift_error(int bytes_read)
{
	if (bytes_read != -1)
		return (false);
	if (errno == EAGAIN || errno == EWOULDBLOCK) // Erros for not data to read // valid error
		return (false);
	return (true);
}

bool	Server::read_request(std::string& buffer)
{
	char	tmp[1024];
	int		bytes_read;

	write_debug("Reading request");
	while (true)
	{
		bytes_read = recv(_client_fd, tmp, 1, 0);
		if (verift_error(bytes_read))
			return (write_error_prefix("read_request"));
		if (bytes_read == 0 || bytes_read == -1)
			break ;
		buffer.append((char*)tmp, bytes_read);
	}
	return (true);
}
