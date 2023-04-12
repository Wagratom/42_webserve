/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:51:02 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/11 22:44:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	capture_new_connections(int& epoll_fd, epoll_event* event)
{
	int	numb_events;

	numb_events = epoll_wait(epoll_fd, event, 10, -1);
	std::cout << "numb_events: " << numb_events << std::endl;
	if (numb_events == -1)
		return (write_error_prefix("save_new_connections"));
	if (numb_events > 0)
		return (true);
	return (true);
}

int	main_loop(server& data)
{
	struct	epoll_event event[10];

	while (true)
	{
		if (!capture_new_connections(data.epoll_fd, event))
			return (1);
		if (save_new_connections(data, event))
			continue ;
	}
}
