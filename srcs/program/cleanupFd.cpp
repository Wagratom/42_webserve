/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanupFd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/13 15:33:27 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::cleanupFd(int fd)
{
	std::cout << "cleanup fd: " << fd << std::endl;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
		return (writeStreerrorPrefix("remove_fd_from_epoll"));
	if (_responses.find(_client_fd)->second != NULL)
	{
		delete _responses.find(_client_fd)->second;
		_responses.find(_client_fd)->second = NULL;
	}
	close(fd);
	return (true);
}
