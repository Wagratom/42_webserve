/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_server_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:33:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/22 20:32:31 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

const int&	Server_configuration::get_port( void ) const
{
	return (this->_port);
}

const std::string&	Server_configuration::get_server_name( void ) const
{
	return (this->_server_name);
}

const std::string&	Server_configuration::get_root( void ) const
{
	return (this->_root);
}

const std::string&	Server_configuration::get_index( void ) const
{
	return (this->_index);
}

const int&	Server_configuration::get_clientMaxBodySize( void ) const
{
	return (this->_clientMaxBodySize);
}

const std::string&	Server_configuration::get_return( void ) const
{
	return (this->_return);
}

const bool&	Server_configuration::get_autoIndex( void ) const
{
	return (this->_autoIndex);
}

const std::map<std::string, std::string*>&	Server_configuration::get_error_page( void ) const
{
	return (this->_error_page);
}

const std::map<std::string, t_location*>&	Server_configuration::get_locations( void ) const
{
	return (this->_locations);
}

const std::map<std::string, std::string>&	Server_configuration::get_cgi( void ) const
{
	return (this->_cgi);
}
