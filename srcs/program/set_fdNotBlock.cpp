/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fdNotBlock.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:37:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 22:53:24 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::set_fdNotBlock( int& fd )
{
	int	properties;

	properties = fcntl(fd, F_GETFL, 0);
	if (properties == -1)
		return (writeStreerrorPrefix("Error: set_fdNotBlock: not get properties"));
	if (fcntl(fd, F_SETFL, properties | O_NONBLOCK) == -1)
		return (writeStreerrorPrefix("Error: set_fdNotBlock: not set properties"));
	return (true);
}
