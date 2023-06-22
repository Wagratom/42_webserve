/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Parser_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:06:08 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/22 16:20:41 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

/*############################################################################*/
/*                         Constructos / Destructors                          */
/*############################################################################*/
Parser_configuration::Parser_configuration( void ) {}

Parser_configuration::Parser_configuration(std::string filename)
 	: _dictionary_server(create_server_dictionary())
	, _server_configuration(create_configuration_server())
	// , _locations(NULL)
	// , _file(NULL)
	// , _save_init_file(NULL)
	, _filename(filename)
{
	initializeUniversalDictionary();
}

Parser_configuration::Parser_configuration( Parser_configuration& src )
{
	if (this != &src)
		*this = src;
}

Parser_configuration::~Parser_configuration( void )
{
	delete _server_configuration;
	for (std::map<std::string, t_location*>::iterator it = _locations.begin(); it != _locations.end(); it++)
	{
		delete it->second->configuration;
		delete it->second;
	}
}


/*############################################################################*/
/*                            Constructos structs                             */
/*############################################################################*/

t_server_dictionary*	Parser_configuration::create_server_dictionary( void )
{
	t_server_dictionary	static dictionary[3] = {
		{"listen", 6, &Parser_configuration::get_port},
		{"server_name", 11, &Parser_configuration::get_server_name},
		{"", 0, NULL}
	};
	return (dictionary);
}

void	Parser_configuration::initializeUniversalDictionary( void )
{
	_dictionary_universal["root"] = &Parser_configuration::get_root;
	_dictionary_universal["index"] = &Parser_configuration::get_index;
	_dictionary_universal["client_max_body_size"] = &Parser_configuration::get_client_max_body_size;
	_dictionary_universal["error_page"] = &Parser_configuration::get_error_page;
}

server_configuration*	Parser_configuration::create_configuration_server( void )
{
	return (new server_configuration);
}
