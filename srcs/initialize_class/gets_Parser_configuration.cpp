/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_Parser_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:49:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 22:07:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

server_configuration*	Parser_configuration::get_server_configuration( void ) {
	return (this->_server_configuration);
}

t_location*	Parser_configuration::get_location_configuration( void )
{
	return (this->_location_configuration);
}

