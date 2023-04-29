/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_configuration_location.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:42 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:31:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	location_configuration::set_location( std::string location )
{
	this->_location = location;
}

void	location_configuration::set_root( std::string root )
{
	this->_root = root;
}

void	location_configuration::set_index( std::string index  )
{
	this->_index = index;
}

void	location_configuration::set_error_page( std::string error_page  )
{
	this->_error_page = error_page;
}

void	location_configuration::set_client_max_body_size( std::string client_max_body_size )
{
	this->_client_max_body_size = client_max_body_size;
}
