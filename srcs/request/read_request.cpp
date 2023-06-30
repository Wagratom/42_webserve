/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/29 10:23:54 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::read_request(std::string& buffer)
{
	int		bytes_read;
	char	tmp[129];
	bool	is_end;

	is_end = false;
	while (is_end == false)
	{
		bytes_read = recv(_client_fd, tmp, 128, 0);
		if (bytes_read == -1)
			return (write_error("Error: read_request"));
		if (bytes_read == 0)
			break;
		if (std::string(tmp).find("\r\n\r\n") != std::string::npos)
			is_end = true;
		tmp[bytes_read] = '\0';
		buffer.append((char*)tmp, bytes_read);
	}
	write_debug(buffer);
	return (true);
}
