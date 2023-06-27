/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_location_configuration.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/27 18:04:46 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

std::string	location_configuration::get_root( void )
{
	return (this->_root);
}

std::string	location_configuration::get_index( void )
{
	return (this->_index);
}

std::string	location_configuration::get_return( void )
{
	return (this->_return);
}

std::map<std::string, std::string*>	location_configuration::get_error_page( void )
{
	return (this->_error_page);
}

int	location_configuration::get_clientMaxBodySize( void )
{
	return (this->_clientMaxBodySize);
}

bool	location_configuration::get_autoIndex( void )
{
	return (this->_autoIndex);
}
