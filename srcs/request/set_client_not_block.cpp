/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_client_no_block.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:37:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 10:37:19 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::set_client_not_block( void )
{
	int	properties;

	properties = fcntl(_client_fd, F_GETFL, 0);
	if (properties == -1)
		return (write_error_prefix("Error: set_client_not_block: not get properties"));
	if (fcntl(_client_fd, F_SETFL, properties | O_NONBLOCK) == -1)
		return (write_error_prefix("Error: set_client_not_block: not set properties"));
	return (true);
}
