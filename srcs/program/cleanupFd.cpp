/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanupFd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/26 11:48:17 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::cleanupFd(epoll_event& event)
{
	if ((int)event.data.fd == _server_fd)
		return (true);
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, event.data.fd, NULL) == -1)
		return (write_error_prefix("remove_fd_from_epoll"));
	close(event.data.fd);
	return (true);
}