/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_max_body_size.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:39:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:35:54 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../auxiliares.hpp"

bool	test_valid_client_max_body_size()
{
	if (!aux_max_body_size("client_max_body_size 1K;", true, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1M;", true, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1G;", true, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size       1M;", true, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size\t\t1M;", true, __LINE__))
		return (false);
	return (true);
}

bool	test_invalid_client_max_body_size()
{
	if (!aux_max_body_size("", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1K", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1M", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1G", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size       1M", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size\t\t1M", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1;", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size 1W;", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size;", false, __LINE__))
		return (false);
	if (!aux_max_body_size("client_max_body_size        ;", false, __LINE__))
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
