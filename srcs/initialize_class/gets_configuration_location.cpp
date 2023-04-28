/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_configuration_location.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 21:26:05 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

std::string	location_configuration::get_location( void )
{
	return (this->_location);
}

std::string location_configuration::get_root( void )
{
	return (this->_root);
}

std::string location_configuration::get_index( void )
{
	return (this->_index);
}

std::string location_configuration::get_error_page( void )
{
	return (this->_error_page);
}

std::string location_configuration::get_client_max_body_size( void )
{
	return (this->_client_max_body_size);
}
