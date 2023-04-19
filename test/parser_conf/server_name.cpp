/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_name.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:23:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 14:55:56 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

Parser_configuration aux;

bool	test_server_valid_name()
{
	if (!equal_or_err_b(aux.get_server_name("server_name www.42sp.org.br;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name localhost localteste;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name lo cal host;"), true, __LINE__))
		return (false);
	return (true);
}

bool	test_server_invalid_name()
{
	if (!equal_or_err_b(aux.get_server_name(""), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name www.42sp.org.br"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name localhost localteste"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name lo cal host"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name            "), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_server_name("server_name;"), false, __LINE__))
		return (false);
	return (true);

}
int main ( void )
{
	if (!test_server_valid_name())
		return (1);
	if (!test_server_invalid_name())
		return (1);
	return (0);
}
