/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false6.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 17:32:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	test_false( void )
{
	Parser_configuration	parser;

	if (equal_or_err_b(parser.parser((char*)"./confis/true_conf5.conf"), false, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	if (test_false() == false)
		return (1);
	return (0);
}