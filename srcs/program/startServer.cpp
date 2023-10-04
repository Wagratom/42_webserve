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
	write_debug_number("checking Timeout process: ", _responses.size());
	std::map<int, Response*>::iterator it = _responses.begin();
	while (it != _responses.end())
	{
		if ((std::time(NULL) -it->second->creationTime) > 10)
		{
			write_debug_number("Timeout process: ", it->first);
			_client_fd = it->first;
			_response = it->second;
			if (responseClientError(ERROR504, getErrorPageMap("504")) == false)
				responseClientError(ERROR500, getErrorPageMap("500"));
			if (waitpid(it->second->process.pid, NULL, WNOHANG) == 0)
				kill(it->second->process.pid, SIGKILL);
			it++;
			cleanupClient(_client_fd);
			status = true;
		}
		else
			it++;
	}
	_lastVerifyTimeout = std::time(NULL);
	return status;
}

bool	Server::captureNewEvents(epoll_event* event, int& numberOfEvents)
{
	numberOfEvents = epoll_wait(_epoll_fd, event, MAX_EVENTS, 3000);
	if (numberOfEvents == -1)
		return (writeStreerrorPrefix("handleNewConnections"));
	return (true);
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
