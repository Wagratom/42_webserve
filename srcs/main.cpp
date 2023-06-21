/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:46:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 19:49:02 by wwallas-         ###   ########.fr       */
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

bool	Server::startServer( void )
{
	if (_parserFile->parseConfigurationFile() == false)
		return (false);
	if (create_server_configured() == false)
		return (false);
	if (start_server() == false)
		return (false);
	return (true);
}

int main ( int argc, char *argv[] )
{
	set_debug(true);
	if (valid_arguments(argc, argv) == false)
		return (false);
	Server	server(argv[1]);
	if (server.startServer() == false)
		return (-1);
	return (0);
}
