/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_location_configuration.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:42 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/23 18:51:36 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	location_configuration::set_root( std::string root )
{
	if (this->_root != "")
		return ;
	if (root[root.length() - 1] != '/')
		root.append("/");
	this->_root = root;
}

void	location_configuration::set_index( std::string index  )
{
	this->_index = index;
}

void	location_configuration::set_error_page( std::string number, std::string error_page  )
{
	if (_error_page.find(number) != _error_page.end())
		return ;
	_error_page[number] = new std::string(error_page);
}

void	location_configuration::set_client_max_body_size( std::string client_max_body_size )
{
	this->_client_max_body_size = client_max_body_size;
}
