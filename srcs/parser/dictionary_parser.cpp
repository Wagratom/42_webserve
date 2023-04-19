/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_parser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:24:27 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 10:17:26 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

t_dictionary_parser*	Parser_configuration::create_dictionary_parser( void )
{
	t_dictionary_parser	static dictionary[] = {
								{"server_name", &Parser_configuration::get_server_name},
								{"client_max_body_size", &Parser_configuration::get_client_max_body_size},
								{"error_page", &Parser_configuration::get_error_page},
								{"", NULL}
	};
	return (dictionary);
}
