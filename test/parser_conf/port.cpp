/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_port.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:01:55 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/18 09:13:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.hpp"

bool	test_numbers()
{
	int	port;

	if (!equal_or_err_b(get_port(const_cast<char*>("listen 8080;"), port), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen     8080;"), port), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen\t\t8080;"), port), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 65535;"), port), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 0;"), port), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen0;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 65536;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen         ;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen\t\t\t;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen -1;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 8a;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 80.;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 0000;"), port), false, __LINE__))
		return (false);
	return (true);
}

bool	test_listen()
{
	int	port;

	if (!equal_or_err_b(get_port(const_cast<char*>("listenn 8080;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("llisten 8080;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("liste 8080;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("isten 65535;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listan 0;"), port), false, __LINE__))
		return (false);
	return (true);
}

bool	test_point()
{
	int	port;

	if (!equal_or_err_b(get_port(const_cast<char*>("listen 8080;"), port), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen 8080:"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listan 0"), port), false, __LINE__))
		return (false);
	return (true);
}

bool	test_random()
{
	int	port;

	if (!equal_or_err_b(get_port(const_cast<char*>(""), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(NULL , port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("listen"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("port 8080;"), port), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_port(const_cast<char*>("8080"), port), false, __LINE__))
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
