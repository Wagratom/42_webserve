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

bool	separate_request_child(server& data, epoll_event* event)
{
	pid_t	pid;

	std::cout << "separate_request_child" << std::endl;
	if (!fork_staus(pid))
		return (false);
	if (pid == CHILD)
	{
		close(data.server_fd);
		handle_request(event);
		std::cout << "sai do filho" << std::endl;
		exit(0);
	}
	return (true);
}
