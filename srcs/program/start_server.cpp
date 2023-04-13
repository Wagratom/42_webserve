/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:47:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/12 09:53:30 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

int	start_server(server& data)
{
	struct	epoll_event event[MAX_EVENTS];

	while (true)
	{
		if (!capture_new_events(data.epoll_fd, event))
			return (-1);
		if (!handle_events(data, event))
			return (-1);
	}
}
