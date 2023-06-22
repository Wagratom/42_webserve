/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 21:05:43 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_true( void )
{
	Server	server("./confis/true3.conf");

	if (equal_or_err_b(server.get_parser()->parseConfigurationFile(), true, __LINE__) == false)
		return (false);
	if (equal_or_err_i(server.get_parser()->get_server_configuration()->get_port() , 8080, __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.get_parser()->get_server_configuration()->get_server_name(), "serve.com", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.get_parser()->get_server_configuration()->get_error_page(), "404 /serve.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.get_parser()->get_server_configuration()->get_client_max_body_size(), "10G", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.get_parser()->get_server_configuration()->get_index(), "sever.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(server.get_parser()->get_server_configuration()->get_root(), "/var/www/server.com", __LINE__) == false)
		return (false);
	return (true);
}

int main( void )
{
	std::cout << "\033[32mTrue 3 em verde!\033[0m" << std::endl;
	if (test_true() == false)
		return (1);
	return (0);
}
