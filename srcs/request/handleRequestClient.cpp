/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleRequestClient.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:24:21 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/01 13:44:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::savaDataCleint(epoll_event& event)
{
	try {
		configureEnvsServer(event);
		createNewResponses();
		return (true);
	} catch (std::exception& e) {
		return  write_error("handle_GET_requesition: " + std::string(e.what()));
	}
}

bool	Server::handleRequestClient( void )
{
	// write_debug_number("handleRequestClient: ", _client_fd);
	if (_response->endHeader == false)
	{
		if (readHeaderRequest() == false)
			return (false);
		if (_response->endHeader == false)
			return (true);
		return (responseRequest());
	}
	if (_response->isProcessAutoindex == true)
		return (handleClientResponse());
	return handlePostBody();
}
