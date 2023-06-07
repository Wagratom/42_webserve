/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_configuration_server.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:40:49 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:30:55 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	server_configuration::set_port( int port )
{
	if (this->_port != -1)
		return ;
	this->_port = port;
}

void	server_configuration::set_server_name( std::string server_name )
{
	if (this->_server_name != "")
		return ;
	this->_server_name = server_name;
}

void	server_configuration::set_root( std::string root )
{
	if (this->_root != "")
		return ;
	if (root[root.length() - 1] != '/')
		root.append("/");
	this->_root = root;
}

void	server_configuration::set_index( std::string index  )
{
	if (this->_index != "")
		return ;
	this->_index = index;
}

void	server_configuration::set_error_page( std::string error_page  )
{
	if (this->_error_page != "")
		return ;
	this->_error_page = error_page;
}

void	server_configuration::set_client_max_body_size( std::string client_max_body_size )
{
	if (this->_client_max_body_size != "")
		return ;
	this->_client_max_body_size = client_max_body_size;
}
