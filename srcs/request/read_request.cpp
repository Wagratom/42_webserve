/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/13 15:37:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

static bool read_request_aux(char* tmp, int& bytes_read, int fd)
{
	bytes_read = recv(fd, tmp, 1024, 0);
	if (std::string(tmp).find("\r\n\r\n") != std::string::npos)
		return (true);
	return (false);
}

bool	Server::read_request(std::string& buffer)
{
	int		bytes_read;
	char	tmp[1024];
	bool	is_end;

	is_end = false;
	while (is_end == false)
	{
		if (read_request_aux(tmp, bytes_read, _client_fd))
			is_end = true;
		buffer.append((char*)tmp, bytes_read);
	}
	write_debug(buffer);
	return (true);
}
