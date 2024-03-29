/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Parser_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:06:08 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/15 11:16:13 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

/*############################################################################*/
/*                            Constructos structs                             */
/*############################################################################*/

void	Parser_configuration::initializeServerDictionary( void )
{
	_dictionary_server["listen"] = &Parser_configuration::get_port;
	_dictionary_server["server_name"] = &Parser_configuration::get_server_name;
	_dictionary_server["timeout"] = &Parser_configuration::get_timeout;
}

void	Parser_configuration::initializeUniversalDictionary( void )
{
	_dictionary_universal["root"] = &Parser_configuration::get_root;
	_dictionary_universal["index"] = &Parser_configuration::get_index;
	_dictionary_universal["client_max_body_size"] = &Parser_configuration::get_clientMaxBodySize;
	_dictionary_universal["error_page"] = &Parser_configuration::get_error_page;
	_dictionary_universal["return"] = &Parser_configuration::get_return;
	_dictionary_universal["autoindex"] = &Parser_configuration::get_autoIndex;
	_dictionary_universal["limit_except"] = &Parser_configuration::get_limit_except;
	_dictionary_universal["cgi"] = &Parser_configuration::get_cgi;
}

/*############################################################################*/
/*                         Constructos / Destructors                          */
/*############################################################################*/
Parser_configuration::Parser_configuration( void ) {}

Parser_configuration::Parser_configuration(std::string filename)
	: _filename(filename)
	, _indexServer(0)
{
	initializeUniversalDictionary();
	initializeServerDictionary();
}

Parser_configuration::~Parser_configuration( void )
{
	for (std::vector<Server_configuration*>::iterator it = _server_configurations.begin(); it != _server_configurations.end(); it++)
		delete *it;
}
