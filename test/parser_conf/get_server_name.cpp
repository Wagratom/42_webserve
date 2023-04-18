/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_server_name.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:23:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/18 09:04:08 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.hpp"

bool	test_server_valid_name()
{
	std::string server_name;

	if (!equal_or_err_b(get_server_name((char*)"server_name www.42sp.org.br;", server_name), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name localhost localteste;", server_name), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name lo cal host;", server_name), true, __LINE__))
		return (false);
	return (true);
}

bool	test_server_invalid_name()
{
	std::string server_name;

	if (!equal_or_err_b(get_server_name(NULL, server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"", server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name www.42sp.org.br", server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name localhost localteste", server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name lo cal host", server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name            ", server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name", server_name), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_server_name((char*)"server_name;", server_name), false, __LINE__))
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
