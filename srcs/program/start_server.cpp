/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:47:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 08:38:22 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

int	Server::start_server( void )
{
	struct	epoll_event event[MAX_EVENTS];

	while (true)
	{
		if (!capture_new_events(event))
			return (-1);
		if (!handle_events(event))
			return (-1);
	}
}
