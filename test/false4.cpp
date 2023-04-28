/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false4.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 14:31:25 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	test_false( void )
{
	Parser_configuration	parser("./confis/false4.conf");

	if (equal_or_err_b(parser.parser(), false, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	if (test_false() == false)
		return (1);
	std::cout << "OK" << std::endl;
	return (0);
}
