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

bool	Server::timeoutHandler( void )
{
	bool	status = false;

	if ((std::time(NULL) -_lastVerifyTimeout) < 5)
		return status;
	write_debug_prefix(CIANO, "checking Timeout ");
	write_debug_number("Number of open clients process: ", _responses.size());
	write_debug(AZUL);
	std::map<int, Response*>::iterator it = _responses.begin();
	while (it != _responses.end())
	{
		if ((std::time(NULL) -it->second->creationTime) > 10)
		{
			write_debug_number("Timeout in client process: ", it->first);
			_client_fd = it->first;
			_serverUsing = _serversConf.at(it->second->port);
			responseClientError(ERROR504, _serverUsing->get_root(), getErrorPageMapServer("504"));
			if (waitpid(it->second->process.pid, NULL, WNOHANG) == 0)
				kill(it->second->process.pid, SIGKILL);
			it++;
			cleanupFd(_client_fd);
			cleanupResponse(_client_fd);
			status = true;
		}
		else
			it++;
	}
	_lastVerifyTimeout = std::time(NULL);
	return status;
}

int	Server::startServer( void )
{
	struct	epoll_event event[MAX_EVENTS];

	write_debug("\033[0;36m\tStarting server\033[0;34m");
	_lastVerifyTimeout = std::time(NULL);
	while (true)
	{
		int	numberOfEvents = 0;
		captureNewEvents(event, numberOfEvents);
		if (timeoutHandler())
			continue ;
		filterEvent(event, numberOfEvents);
	}
}
