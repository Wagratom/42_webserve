/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKeepAlive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/13 16:50:55 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handleKeepAlive( void )
{
	std::string	typeConnection = getenv("HTTP_CONNECTION");
	if (typeConnection == "keep-alive")
		write_debug("Keep-Alive");
	else
	{
		write_debug_number("Close: ", _client_fd);
		cleanupFd(_client_fd);
	}
	return (true);
}
