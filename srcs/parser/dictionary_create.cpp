/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_create.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:06:08 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 13:29:54 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>


t_server_dictionary*	Parser_configuration::create_server_dictionary( void )
{
	t_server_dictionary	static dictionary[3] = {
								{"listen", &Parser_configuration::get_port},
								{"server_name", &Parser_configuration::get_server_name},
								{"", NULL}
	};
	return (dictionary);
}


t_universal_dictionary*	Parser_configuration::create_universal_dictionary( void )
{
	t_universal_dictionary	static dictionary2[6] = {
								{"root", &Parser_configuration::get_root},
								{"index", &Parser_configuration::get_index},
								{"client_max_body_size", &Parser_configuration::get_client_max_body_size},
								{"error_page", &Parser_configuration::get_error_page},
								{"", NULL}
	};
	return (dictionary2);
}

configuration_server*	Parser_configuration::create_configuration_server( void )
{
	return (new configuration_server);
}

configuration_location*	Parser_configuration::create_configuration_location( void )
{
	return (new configuration_location);
}
