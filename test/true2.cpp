/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/27 11:43:31 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	test_true( void )
{
	Parser_configuration	parser ("./confis/true_conf2.conf");

	if (equal_or_err_b(parser.parser(), true, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	if (test_true() == false)
		return (1);
	return (0);
}
