/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_location_configuration.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/22 18:43:27 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

const std::string&	Location_configuration::get_root( void ) const
{
	return (this->_root);
}

const std::string&	Location_configuration::get_index( void ) const
{
	return (this->_index);
}

const std::string&	Location_configuration::get_return( void ) const
{
	return (this->_return);
}

const std::map<std::string, std::string*>&	Location_configuration::get_error_page( void ) const
{
	return (this->_error_page);
}

const int&	Location_configuration::get_clientMaxBodySize( void ) const
{
	return (this->_clientMaxBodySize);
}

const bool&	Location_configuration::get_autoIndex( void ) const
{
	return (this->_autoIndex);
}

const std::vector<std::string>&	Location_configuration::get_limit_except( void ) const
{
	return (this->_limit_except);
}

const std::map<std::string, std::string>&	Location_configuration::get_cgi( void ) const
{
	return (this->_cgi);
}
