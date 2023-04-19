/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_max_body_size.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:39:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 10:19:13 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

Parser_configuration aux;

bool	test_valid_client_max_body_size()
{
	std::string	client_max_body_size;

	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1K;", client_max_body_size), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1M;", client_max_body_size), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1G;", client_max_body_size), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size       1M;", client_max_body_size), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size\t\t1M;", client_max_body_size), true, __LINE__))
		return (false);
	return (true);
}

bool	test_invalid_client_max_body_size()
{
	std::string	client_max_body_size;

	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size(NULL, client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1K", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1M", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1G", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size       1M", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size\t\t1M", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1;", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size 1W;", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size;", client_max_body_size), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_client_max_body_size((char*)"client_max_body_size        ;", client_max_body_size), false, __LINE__))
		return (false);
	return (true);
}
int main( void )
{
	if (!test_valid_client_max_body_size())
		return (1);
	if (!test_invalid_client_max_body_size())
		return (1);
	return (0);
}
