/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:06:40 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 17:05:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	test_true( void )
{
	Parser_configuration	parser ("./confis/true2.conf");
	Server					server(parser.get_server(), *parser.get_location());
	server_configuration*	tmp = server.get_server_congifuration();
	t_location_settings**	tmp2 = parser.get_location();

	std::cout << "locationName: " << (*tmp2)->locationName << std::endl;

	if (equal_or_err_b(parser.parser(), true, __LINE__) == false)
		return (false);
	if (equal_or_err_i(tmp->get_port() , 80, __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_server_name(), "serve.com", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_error_page(), "404 /serve.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_client_max_body_size(), "10G", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_index(), "sever.html", __LINE__) == false)
		return (false);
	if (equal_or_err_s(tmp->get_root(), "/var/www/server.com", __LINE__) == false)
		return (false);

	//             location

	// if (equal_or_err_s(tmp2->locationName, "/", __LINE__) == false)
		// return (false);


	return (true);
}

int main( void )
{
	if (test_true() == false)
		return (1);
	std::cout << "OK" << std::endl;
	return (0);
}
