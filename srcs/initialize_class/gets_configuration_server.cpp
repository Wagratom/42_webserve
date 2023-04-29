/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_configuration_server.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:33:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

int	server_configuration::get_port( void )
{
	return (this->_port);
}

std::string server_configuration::get_server_name( void )
{
	return (this->_server_name);
}

std::string server_configuration::get_root( void )
{
	return (this->_root);
}

std::string server_configuration::get_index( void )
{
	return (this->_index);
}

std::string server_configuration::get_error_page( void )
{
	return (this->_error_page);
}

std::string server_configuration::get_client_max_body_size( void )
{
	return (this->_client_max_body_size);
}
