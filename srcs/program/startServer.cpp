/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:47:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 10:48:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::timeoutHandler( void )
{
	write_debug_number("Number of open clients process: ", _responses.size());
	if ((std::time(NULL) -_lastVerifyTimeout) < 3)
		return ;
	write_debug_prefix(CIANO, "checking Timeout ");
	write_debug(AZUL);
	for (std::map<int, Response*>::iterator it = _responses.begin(); it != _responses.end(); it++)
	{
		if ((std::time(NULL) -it->second->creationTime) > 3)
		{
			write_debug_number("Timeout in client process: ", it->first);
			_client_fd = it->first;
			responseClientError(ERROR504, _serverUsing->get_root(), getErrorPageMapServer("504"));
			kill(it->second->process.pid, SIGKILL);
			cleanupFd(_client_fd);
		}
	}
	_lastVerifyTimeout = std::time(NULL);
}

int	Server::startServer( void )
{
	struct	epoll_event event[MAX_EVENTS];

	write_debug("\033[0;36m\tStarting server\033[0;34m");
	_lastVerifyTimeout = std::time(NULL);
	while (true)
	{
		int	numberOfEvents = 0;
		if (!captureNewEvents(event, numberOfEvents))
			return (-1);
		timeoutHandler();
		if (!filterEvent(event, numberOfEvents))
			return (-1);
		write_debug("\n");
	}
}
