/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_POST_request.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/12 21:26:25 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

struct aux_upload{
	std::string	request = "";
	int			body_length = 0;
	char		buffer[1024] = {0};
	int			bytes_read = 0;
};

bool	Server::handle_POST_requesition()
{
	if (_parser_request->get_endPoint() == "/upload")
		return (handle_update());
	return (true);
}

bool	Server::handle_update()
{
	aux_upload data;

	data.request = _parser_request->get_request();
	data.body_length = data.request.length();
	while (true)
	{
		data.bytes_read = read(_client_fd, data.buffer, 1024);
		data.body_length += data.bytes_read;
		data.request += data.buffer;
		// TODO: check if the body is bigger than client_max_body_size
	}
	return (true);
}
