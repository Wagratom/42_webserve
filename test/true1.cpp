/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 21:26:37 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_true( void )
{
	Server	server("./confis/true1.conf");

	if (equal_or_err_b(server.get_parser()->controlParserConfiguration(), true, __LINE__) == false)
		return (false);
	if (equal_or_err_i(server.server()->get_port(), 8080, __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.server()->get_server_name(), "serve.com server2", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.server()->get_error_page(), "404 /serve.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.server()->get_client_max_body_size(), "10G", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.server()->get_index(), "sever.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.server()->get_root(), "/var/www/server.com/", __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	std::cout << "\033[32mTrue 1 em verde!\033[0m" << std::endl;
	if (test_true() == false)
		return (1);
	return (0);
}
