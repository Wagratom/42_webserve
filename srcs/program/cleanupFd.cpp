/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanupFd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/19 13:19:29 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

void	Server::cleanupResponse( int& fd )
{
	std::map<int, Response*>::iterator it = _responses.find(fd);
	if (it != _responses.end() && it->second != NULL)
	{
		delete it->second;
		it->second = NULL;
		_responses.erase(it);
	}
}

bool	Server::cleanupFd(int fd)
{
	write_debug_number("cleanupFd: ", fd);
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
		return (writeStreerrorPrefix("remove_fd_from_epoll"));
	close(fd);
	return (true);
}
