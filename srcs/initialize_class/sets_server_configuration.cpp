/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_server_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:40:49 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 20:55:03 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	Server_configuration::set_port( int port )
{
	if (this->_port != -1)
		return ;
	this->_port = port;
}

void	Server_configuration::set_server_name( std::string server_name )
{
	if (this->_server_name != "")
		return ;
	this->_server_name = server_name;
}

void	Server_configuration::set_root( std::string root )
{
	if (this->_root != "")
		return ;
	if (root[root.length() - 1] != '/')
		root.append("/");
	this->_root = root;
}

void	Server_configuration::set_index( std::string index  )
{
	if (this->_index != "")
		return ;
	this->_index = index;
}


void	Server_configuration::set_autoIndex( bool autoIndex )
{
	this->_autoIndex = autoIndex;
}

void	Server_configuration::set_client_max_body_size( int maxSize )
{
	if (this->_clientMaxBodySize != 0)
		return ;
	this->_clientMaxBodySize = maxSize;
}

void	Server_configuration::set_return( std::string return_ )
{
	if (this->_return != "")
		return ;
	this->_return = return_;
}

void	Server_configuration::set_error_page( std::string number, std::string error_page)
{
	if (_error_page.find(number) != _error_page.end())
		return ;
	_error_page[number] = new std::string(error_page);
}

void	Server_configuration::set_locations( std::string location_name, t_location* location )
{
	this->_locations[location_name] = location;
}
