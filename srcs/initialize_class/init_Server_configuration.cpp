/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Server_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:12:17 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/10 21:09:34 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

Server_configuration::Server_configuration( void )
	: aux_configuration()
	, _port(-1)
	, _clientMaxBodySize(0)
	, _server_name("")
	, _root("")
	, _index("")
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
};
