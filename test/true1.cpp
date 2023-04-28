/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 16:01:31 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_true( void )
{
	Parser_configuration	parser("./confis/true1.conf");
	Server					server(parser.get_server(), parser.get_location());
	server_configuration*	tmp = server.get_server_congifuration();

	if (equal_or_err_b(parser.parser(), true, __LINE__) == false)
		return (false);
	if (equal_or_err_i(tmp->get_port() , 8080, __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_server_name(), "serve.com server2", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_error_page(), "404 /serve.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_client_max_body_size(), "10G", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_index(), "sever.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_root(), "/var/www/server.com", __LINE__) == false)
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
