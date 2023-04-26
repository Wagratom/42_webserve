/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_configuration_server.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:40:49 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 09:59:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	configuration_server::set_port( int port )
{
	this->_port = port;
}

void	configuration_server::set_server_name( std::string server_name )
{
	this->_server_name = server_name;
}

void	configuration_server::set_root( std::string root )
{
	this->_root = root;
}

void	configuration_server::set_index( std::string index  )
{
	this->_index = index;
}

void	configuration_server::set_error_page( std::string error_page  )
{
	this->_error_page = error_page;
}

void	configuration_server::set_client_max_body_size( std::string client_max_body_size )
{
	this->_client_max_body_size = client_max_body_size;
}
