/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true6.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 20:18:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_false( void )
{
	Parser_configuration	parser("./confis/true_conf6.conf");

	if (equal_or_err_b(parser.parser(), false, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	std::cout << "\033[32mTrue 6 em verde!\033[0m" << std::endl;
	if (test_false() == false)
		return (1);
	std::cout << "OK" << std::endl;
	return (0);
}
