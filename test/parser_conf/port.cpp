/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:01:55 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 15:05:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

Parser_configuration aux;

bool	test_numbers()
{
	if (!equal_or_err_b(aux.get_port("listen 8080;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen     8080;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen\t\t8080;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 65535;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 0;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen0;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 65536;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen         ;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen\t\t\t;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen -1;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 8a;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 80.;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 0000;"), false, __LINE__))
		return (false);
	return (true);
}

bool	test_listen()
{
	int	port;

	if (!equal_or_err_b(aux.get_port("listenn 8080;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("llisten 8080;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("liste 8080;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("isten 65535;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listan 0;"), false, __LINE__))
		return (false);
	return (true);
}

bool	test_point()
{
	int	port;

	if (!equal_or_err_b(aux.get_port("listen 8080;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen 8080:"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listan 0"), false, __LINE__))
		return (false);
	return (true);
}

bool	test_random()
{
	int	port;

	if (!equal_or_err_b(aux.get_port(""), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("listen"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("port 8080;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_port("8080"), false, __LINE__))
		return (false);
	return (true);
}

int main ( void )
{
	if (!test_numbers())
		return (1);
	if (!test_listen())
		return (1);
	if (!test_point())
		return (1);
	if (!test_random())
		return (1);
	return (0);
}
