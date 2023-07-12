/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKeepAlive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 16:07:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handleKeepAlive( void )
{
	std::string	typeConnection = getenv("HTTP_CONNECTION");
	if (typeConnection != "keep-alive")
		cleanupFd(_client_fd);
	return (true);
}
