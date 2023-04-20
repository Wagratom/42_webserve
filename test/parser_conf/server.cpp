/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:52:20 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:31:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../auxiliares.hpp"

bool	test_valid_server()
{
	if (aux_server("server {", true, __LINE__) == false)
		return (false);
	if (aux_server("server{", true, __LINE__) == false)
		return (false);
	if (aux_server("server\t\t{", true, __LINE__) == false)
		return (false);
	if (aux_server("server        {", true, __LINE__) == false)
		return (false);
	return (true);
}

bool	test_invalid_server()
{
	if (aux_server("server", false, __LINE__) == false)
		return (false);
	if (aux_server("server { a\t\t{", false, __LINE__) == false)
		return (false);
	if (aux_server("server        {a", false, __LINE__) == false)
		return (false);
	if (aux_server("server        {{", false, __LINE__) == false)
		return (false);
	if (aux_server("server        }", false, __LINE__) == false)
		return (false);
	return (true);
}
int main( void )
{
	if (test_valid_server() == false)
		return (1);
	if (test_invalid_server() == false)
		return (1);
	return (0);
}
