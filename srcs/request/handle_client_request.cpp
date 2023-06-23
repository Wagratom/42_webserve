/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client_request.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 14:35:22 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_client_request(epoll_event& event)
{
	std::string	buffer;

	write_debug("\nClient seed request");
	if (event.events & EPOLLOUT)
		_write = true;
	_client_fd = event.data.fd;
	if (set_fdNotBlock(_client_fd) == false)
		return (false);
	if (read_request(buffer) == false)
		return (false);
	if (response_request(buffer) == false)
		return (false);
	return (true);
}
