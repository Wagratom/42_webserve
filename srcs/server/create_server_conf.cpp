/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server_conf.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/13 08:50:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_serve.hpp>

bool	Server::create_server_configured( void )
{
	if (!create_server())
		return (false);
	if (!conf_serve_to_read())
		return (false);
	return (true);
}
