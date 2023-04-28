/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false5.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/27 22:19:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	test_false( void )
{
	Parser_configuration	parser("./confis/false_conf5.conf");

	if (equal_or_err_b(parser.parser(), false, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	if (test_false() == false)
		return (1);
	return (0);
}
