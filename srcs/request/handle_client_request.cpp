/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client_request.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 08:58:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_client_request(epoll_event& event)
{
	std::string	buffer;

	_client_fd = event.data.fd;
	if (set_client_no_block() == false)
		return (false);
	if (read_request(buffer) == false)
		return (false);
	std::cout << buffer << std::endl;
	if (parse_request(buffer) == false)
		return (false);
	if (response_request() == false)
		return (false);
	return (true);
}
