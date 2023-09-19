/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:46:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 21:19:14 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	valid_arguments( int argc, char *argv[])
{
	write_debug("Validating arguments");
	if (argc > 3 || argc <= 1)
		return (write_error("Error: Invalid number of arguments"));
	if (argv == NULL || *argv == 0)
		return (write_error("Error: Invalid arguments"));
	if (argv[2] && std::string(argv[2]) == "DEBUG")
		set_debug(true);
	return (true);
}

bool	Server::initializeServer( void )
{
	if (_parserFile->controlParserConfiguration() == false)
		return (false);
	if (createServerConfigured() == false)
		return (false);
	if (startServer() == false)
		return (false);
	return (true);
}

int main ( int argc, char *argv[] )
{
	// set_debug(true);
	if (valid_arguments(argc, argv) == false)
		return (false);
	Server	server(argv[1]);
	if (server.initializeServer() == false)
		return (-1);
	return (0);
}
