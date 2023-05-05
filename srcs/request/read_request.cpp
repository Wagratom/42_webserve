/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 11:40:53 by wwallas-         ###   ########.fr       */
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

static long int	get_multiplier(std::string client_max_body_size)
{
	int	end_string;

	end_string = client_max_body_size.length() - 1;
	if (client_max_body_size[end_string] == 'K')
		return (1024);
	else if (client_max_body_size[end_string] == 'M')
		return (1024 * 1024);
	else if (client_max_body_size[end_string] == 'G')
		return (1024 * 1024 * 1024);
	return (1);
}

static long int	generete_client_max_body_size(std::string client_max_body_size)
{
	int long	max_body_size;
	int			end_string;
	int			multiplier;

	end_string = client_max_body_size.length() - 1;
	multiplier = get_multiplier(client_max_body_size);
	if (!isdigit(client_max_body_size[end_string]))
		client_max_body_size.erase(end_string);
	max_body_size = std::atoi(client_max_body_size.c_str());
	max_body_size *= multiplier;
	return (max_body_size);
}

bool	Server::read_request(std::string& buffer)
{
	char		tmp[1024];
	int			bytes_read;
	long int	bytes_total;
	long int	max_body_size;

	bytes_total = 0;
	max_body_size = generete_client_max_body_size(server()->get_client_max_body_size());
	while (true)
	{
		bytes_read = recv(_client_fd, tmp, 1024, 0);
		if (verift_error(bytes_read))
			return (write_error_prefix("read_request"));
		if (bytes_read == 0 || bytes_read == -1)
			break ;
		bytes_total += bytes_read;
		if (bytes_total > max_body_size)
			return (write_error_prefix("Error: read_request: 413 Payload Too Large"));
		buffer.append((char*)tmp, bytes_read);
	}
	return (true);
}
