/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_configuration_server.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:33:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 09:39:55 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

int	configuration_server::get_port( void )
{
	return (this->_port);
}

std::string configuration_server::get_server_name( void )
{
	return (this->_server_name);
}

std::string configuration_server::get_root( void )
{
	return (this->_root);
}

std::string configuration_server::get_index( void )
{
	return (this->_index);
}

std::string configuration_server::get_error_page( void )
{
	return (this->_error_page);
}

std::string configuration_server::get_client_max_body_size( void )
{
	return (this->_client_max_body_size);
}
