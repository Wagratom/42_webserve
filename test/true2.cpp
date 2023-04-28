/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 14:31:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_true( void )
{
	Parser_configuration	parser ("./confis/true2.conf");
	Server					server(parser.get_server(), parser.get_location());

	if (equal_or_err_b(parser.parser(), true, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	if (test_true() == false)
		return (1);
	std::cout << "OK" << std::endl;
	return (0);
}
