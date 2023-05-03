/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_client_no_block.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 21:39:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::set_client_no_block( void )
{
	int	flags	= fcntl(_client_fd, F_GETFL, 0);

	if (flags == -1)
		return (write_error_prefix("Error: set_client_no_block: not get properties"));
	if (fcntl(_client_fd, F_SETFL, flags | O_NONBLOCK) == -1)
		return (write_error_prefix("Error: set_client_no_block: not set properties"));
	return (true);
}
