/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_create.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:06:08 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 14:55:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>


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

configuration_server*	Parser_configuration::create_configuration_server( void )
{
	return (new configuration_server);
}

configuration_location*	Parser_configuration::create_configuration_location( void )
{
	return (new configuration_location);
}
