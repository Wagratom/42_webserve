/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:46:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/10 11:17:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	valid_arguments( int argc, char *argv[])
{
	if (argc != 2)
		return (write_error("Error: Invalid number of arguments"));
	if (argv == NULL || *argv == 0)
		return (write_error("Error: Invalid arguments"));
	std::cout << "Valid arguments" << std::endl;
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
	set_debug(true);
	if (valid_arguments(argc, argv) == false)
		return (false);
	Server	server(argv[1]);
	if (server.initializeServer() == false)
		return (-1);
	return (0);
}
