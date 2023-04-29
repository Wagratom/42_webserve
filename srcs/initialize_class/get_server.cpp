/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:49:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:49 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

server_configuration*	Parser_configuration::get_server_configuration( void ) {
	return (this->_server_configuration);
}

t_location_settings*	Parser_configuration::get_location_configuration( void )
{
	return (this->_location_configuration);
}

