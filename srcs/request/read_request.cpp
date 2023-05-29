/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 12:39:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::read_request_status(char* tmp, int& bytes_read)
{
	bytes_read = recv(_client_fd, tmp, 1024, 0);
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
		if (read_request_status(tmp, bytes_read))
			is_end = true;
		buffer.append((char*)tmp, bytes_read);
	}
	return (true);
}
