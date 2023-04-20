/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:01:55 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 11:57:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../auxiliares.hpp"

bool	test_numbers()
{
	if (!aux_port("listen 8080;", true, __LINE__))
		return (false);
	if (!aux_port("listen     8080;", true, __LINE__))
		return (false);
	if (!aux_port("listen\t\t8080;", true, __LINE__))
		return (false);
	if (!aux_port("listen 65535;", true, __LINE__))
		return (false);
	if (!aux_port("listen 0;", true, __LINE__))
		return (false);
	if (!aux_port("listen0;", false, __LINE__))
		return (false);
	if (!aux_port("listen 65536;", false, __LINE__))
		return (false);
	if (!aux_port("listen         ;", false, __LINE__))
		return (false);
	if (!aux_port("listen\t\t\t;", false, __LINE__))
		return (false);
	if (!aux_port("listen -1;", false, __LINE__))
		return (false);
	if (!aux_port("listen 8a;", false, __LINE__))
		return (false);
	if (!aux_port("listen 80.;", false, __LINE__))
		return (false);
	if (!aux_port("listen 0000;", false, __LINE__))
		return (false);
	return (true);
}

bool	test_listen()
{
	int	port;

	if (!aux_port("listenn 8080;", false, __LINE__))
		return (false);
	if (!aux_port("llisten 8080;", false, __LINE__))
		return (false);
	if (!aux_port("liste 8080;", false, __LINE__))
		return (false);
	if (!aux_port("isten 65535;", false, __LINE__))
		return (false);
	if (!aux_port("listan 0;", false, __LINE__))
		return (false);
	return (true);
}

bool	test_point()
{
	int	port;

	if (!aux_port("listen 8080;", true, __LINE__))
		return (false);
	if (!aux_port("listen 8080:", false, __LINE__))
		return (false);
	if (!aux_port("listan 0", false, __LINE__))
		return (false);
	return (true);
}

bool	test_random()
{
	int	port;

	if (!aux_port("", false, __LINE__))
		return (false);
	if (!aux_port("listen", false, __LINE__))
		return (false);
	if (!aux_port("port 8080;", false, __LINE__))
		return (false);
	if (!aux_port("8080", false, __LINE__))
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
	std::cout << "Suscess!" << std::endl;
	return (0);
}
