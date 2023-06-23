/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_server_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:40:49 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 18:49:01 by wwallas-         ###   ########.fr       */
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

void	server_configuration::set_error_page( std::string number, std::string error_page)
{
	if (_error_page.find(number) != _error_page.end())
		return ;
	std::cout << "number: " << number << std::endl;
	std::cout << "error_page: " << error_page << std::endl;
	_error_page[number] = new std::string(error_page);
}

void	server_configuration::set_client_max_body_size( std::string client_max_body_size )
{
	if (this->_client_max_body_size != "")
		return ;
	this->_client_max_body_size = client_max_body_size;
}
