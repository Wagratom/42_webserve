/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:09:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 08:03:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.hpp"

bool	valid_test_get_error()
{
	std::string	error_page;

	if (!equal_or_err_b(get_error_page((char*)"error_page 404 /404.html;", error_page), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page       404 /404.html;", error_page), true, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page\t\t\t404 /404.html;", error_page), true, __LINE__))
		return (false);
	return (true);
}

bool	invalid_test_get_error()
{
	std::string	error_page;

	if (!equal_or_err_b(get_error_page(NULL, error_page), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"", error_page), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page 404 /404.html", error_page), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page /404.html;", error_page), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page 404 ;", error_page), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page 404 /404;", error_page), false, __LINE__))
		return (false);
	if (!equal_or_err_b(get_error_page((char*)"error_page;", error_page), false, __LINE__))
		return (false);
	return (true);
}

int main( void )
{
	if (!valid_test_get_error())
		return (1);
	if (!invalid_test_get_error())
		return (1);
	return (0);
}
