/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Location_configuration.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:12:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/15 11:30:33 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

Location_configuration:: Location_configuration( void )
	:  aux_configuration()
	, _error_page()
	, _limit_except()
	, _return("")
	, _index("")
	, _root("")
	, _autoIndex(false)
	, _clientMaxBodySize(0)
{};

Location_configuration::~Location_configuration( void ) {
	std::map<std::string, std::string*>::iterator it = _error_page.begin();
	while (it != _error_page.end())
	{
		delete it->second;
		it++;
	}
	for (std::map<std::string, std::string>::iterator it = _cgi.begin(); it != _cgi.end(); it++)
	{
		it->second.clear();
	}
};
