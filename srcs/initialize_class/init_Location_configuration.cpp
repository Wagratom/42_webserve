/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Location_configuration.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:12:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/02 11:36:50 by wwallas-         ###   ########.fr       */
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
	, _clientMaxBodySize(1000000)
{};

Location_configuration::~Location_configuration( void ) {
	for (std::map<std::string, std::string *>::iterator it = _error_page.begin(); it != _error_page.end(); it++)
		delete it->second;
};
