/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_location_configuration.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:52:42 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 09:52:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	Location_configuration::set_root( std::string root )
{
	if (this->_root != "")
		return ;
	if (root[root.length() - 1] != '/')
		root.append("/");
	this->_root = root;
}

void	Location_configuration::set_index( std::string index  )
{
	if (this->_index != "")
		return ;
	this->_index = index;
}

void	Location_configuration::set_return( std::string index  )
{
	if (this->_return != "")
		return ;
	this->_return = index;
}

void	Location_configuration::set_error_page( std::string number, std::string error_page  )
{
	if (_error_page.find(number) != _error_page.end())
		return ;
	_error_page[number] = new std::string(error_page);
}

void	Location_configuration::set_client_max_body_size( int maxSize )
{
	if (this->_clientMaxBodySize != 0)
		return ;
	this->_clientMaxBodySize = maxSize;
}

void	Location_configuration::set_autoIndex( bool autoIndex )
{
	this->_autoIndex = autoIndex;
}

void	Location_configuration::set_limit_except( std::vector<std::string> method )
{
	if (this->_limit_except.size() != 0)
		return ;
	this->_limit_except = method;
}


