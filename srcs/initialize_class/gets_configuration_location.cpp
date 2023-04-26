/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_configuration_location.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 10:01:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

std::string	configuration_location::get_location( void )
{
	return (this->_location);
}

std::string configuration_location::get_root( void )
{
	return (this->_root);
}

std::string configuration_location::get_index( void )
{
	return (this->_index);
}

std::string configuration_location::get_error_page( void )
{
	return (this->_error_page);
}

std::string configuration_location::get_client_max_body_size( void )
{
	return (this->_client_max_body_size);
}
