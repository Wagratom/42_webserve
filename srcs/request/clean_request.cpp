/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:15:10 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/03 12:15:18 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::clean_request(epoll_event& event)
{
	std::cout << "removendo fd do epoll" << std::endl;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, event.data.fd, NULL) == -1)
		return (write_error_prefix("remove_fd_from_epoll"));
	close(event.data.fd);
	return (true);
}
