/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:46:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/26 15:02:59 by wwallas-         ###   ########.fr       */
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

bool	setup( char* filename )
{
	Parser_configuration	parser(filename);
	Server	server(parser.get_server());

	if (parser.parser() == false)
		return (false);
	if (server.create_server_configured() == false)
		return (false);
	// if (server.start_server() == false)
		// return (false);
	return (true);
}

int main ( int argc, char *argv[] )
{
	if (valid_arguments(argc, argv) == false)
		return (false);
	if (setup(argv[1]) == false)
		return (false);

	return (0);
}
