/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client_request.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 10:33:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_client_request(epoll_event& event)
{
	std::string	buffer;

	write_debug("\nClient seed request");
	_client_fd = event.data.fd;
	if (set_client_not_block() == false)
		return (false);
	if (read_request(buffer) == false)
		return (false);
	if (response_request(buffer) == false)
		return (false);
	// epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, _client_fd, NULL);
	// close(_client_fd);
	return (true);
}
