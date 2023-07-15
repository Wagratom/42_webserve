/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Server_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:12:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/15 11:27:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

Server_configuration::Server_configuration( void )
	: aux_configuration()
	, _error_page()
	, _locations()
	, _server_name("")
	, _return("")
	, _index("")
	, _root("")
	, _clientMaxBodySize(0)
	, _autoIndex(false)
	, _timeout(-1)
	, _port(-1)
{};

Server_configuration::~Server_configuration( void ) {
	for (std::map<std::string, std::string*>::iterator it = _error_page.begin(); it != _error_page.end(); it++)
		delete it->second;
	for (std::map<std::string, t_location*>::iterator it = _locations.begin(); it != _locations.end(); it++)
	{
		delete it->second->configuration;
		delete it->second;
		it->second = NULL;
	}
	for (std::map<std::string, std::string>::iterator it = _cgi.begin(); it != _cgi.end(); it++)
	{
		it->second.clear();
	}
};
