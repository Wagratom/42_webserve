/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:46:34 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 13:30:08 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>


bool	valid_arguments( int argc, char *argv[])
{
	if (argc != 2)
		return (write_error("Error: Invalid number of arguments"));
	if (argv == NULL || *argv == 0)
		return (write_error("Error: Invalid arguments"));
	std::cout << "Valid arguments" << std::endl;
	return (true);
}

int main ( int argc, char *argv[] )
{

	Parser_configuration	parser;

	if (valid_arguments(argc, argv) == false)
		return (false);
	if (parser.parser(argv[1]) == false)
		return (false);
	return (0);
}
