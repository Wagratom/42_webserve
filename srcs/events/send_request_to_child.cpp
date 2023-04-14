/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_request_to_child.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:23:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 10:14:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::send_request_to_child(epoll_event& event)
{
	pid_t	pid;

	if (!fork_staus(pid))
		return (false);
	if (pid == CHILD)
		handle_request_in_cuild(event);
	return (true);
}
