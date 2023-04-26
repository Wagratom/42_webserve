/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_configuration_location.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:42 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 10:04:01 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	configuration_location::set_location( std::string location )
{
	this->_location = location;
}

void	configuration_location::set_root( std::string root )
{
	this->_root = root;
}

void	configuration_location::set_index( std::string index  )
{
	this->_index = index;
}

void	configuration_location::set_error_page( std::string error_page  )
{
	this->_error_page = error_page;
}

void	configuration_location::set_client_max_body_size( std::string client_max_body_size )
{
	this->_client_max_body_size = client_max_body_size;
}
