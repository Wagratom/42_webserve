/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_request_child.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:23:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 10:27:35 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	Server::separate_request_child(epoll_event& event)
{
	pid_t	pid;

	if (!fork_staus(pid))
		return (false);
	if (pid == CHILD)
		handle_request_in_cuild(event);
	return (true);
}
