/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_server_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:33:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 10:19:45 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

int	Server_configuration::get_port( void )
{
	return (this->_port);
}

std::string Server_configuration::get_server_name( void )
{
	return (this->_server_name);
}

std::string Server_configuration::get_root( void )
{
	return (this->_root);
}

std::string Server_configuration::get_index( void )
{
	return (this->_index);
}

std::map<std::string, std::string*>	Server_configuration::get_error_page( void )
{
	return (this->_error_page);
}

int	Server_configuration::get_clientMaxBodySize( void )
{
	return (this->_clientMaxBodySize);
}

std::string	Server_configuration::get_return( void )
{
	return (this->_return);
}

bool	Server_configuration::get_autoIndex( void )
{
	return (this->_autoIndex);
}
