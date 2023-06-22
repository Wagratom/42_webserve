/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_Parser_configuration.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:06:08 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/22 14:11:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

/*############################################################################*/
/*                         Constructos / Destructors                          */
/*############################################################################*/
Parser_configuration::Parser_configuration( void ) {}

Parser_configuration::Parser_configuration(std::string filename)
 	: _dictionary_server(create_server_dictionary())
	, _dictionary_universal(create_universal_dictionary())
	, _server_configuration(create_configuration_server())
	// , _locations(NULL)
	// , _file(NULL)
	// , _save_init_file(NULL)
	, _filename(filename)
{}

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

t_universal_dictionary*	Parser_configuration::create_universal_dictionary( void )
{
	t_universal_dictionary	static dictionary2[6] = {
		{"root", 4, &Parser_configuration::get_root},
		{"index", 5, &Parser_configuration::get_index},
		{"client_max_body_size", 20, &Parser_configuration::get_client_max_body_size},
		{"error_page", 10, &Parser_configuration::get_error_page},
		{"", 0, NULL}
	};
	return (dictionary2);
}

server_configuration*	Parser_configuration::create_configuration_server( void )
{
	return (new server_configuration);
}
