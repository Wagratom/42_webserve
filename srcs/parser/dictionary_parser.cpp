/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_parser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:24:27 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 09:28:16 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

t_dictionary_parser*	Parser_configuration::create_dictionary_parser( void )
{
	t_dictionary_parser	static dictionary[7] = {
								{"listen", &Parser_configuration::get_port},
								{"server_name", &Parser_configuration::get_server_name},
								{"error_page", &Parser_configuration::get_error_page},
								{"client_max_body_size", &Parser_configuration::get_client_max_body_size},
								{"root", &Parser_configuration::get_root},
								{"index", &Parser_configuration::get_index},
								{"", NULL}
	};
	return (dictionary);
}
