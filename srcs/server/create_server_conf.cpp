/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server_conf.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:52:52 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/13 15:18:14 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::create_server_configured( void )
{
	write_debug("\033[0;36m\tCreating server configured\033[0;34m");

	if (create_server() == false)
		return (false);
	if (conf_serve_to_read() == false)
		return (false);
	write_debug("\tData Server");
	write_debug_number("Port: ", _parser_file->get_server_configuration()->get_port());
	write_debug_prefix("ServerName: ", _parser_file->get_server_configuration()->get_server_name());
	write_debug("\033[32mOk XD\n\033[0;37m");
	return (true);
}
