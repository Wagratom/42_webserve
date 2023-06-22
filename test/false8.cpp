/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false8.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 21:05:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_false( void )
{
	Server	server("./confis/false8.conf");

	if (equal_or_err_b(server.get_parser()->parseConfigurationFile(), false, __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	std::cout << "\033[32mFalse 8 em verde!\033[0m" << std::endl;
	if (test_false() == false)
		return (1);
	return (0);
}
