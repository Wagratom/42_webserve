/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:09:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 14:55:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

Parser_configuration aux;

bool	valid_test_get_error()
{
	if (!equal_or_err_b(aux.get_error_page("error_page 404 /404.html;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page       404 /404.html;"), true, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page\t\t\t404 /404.html;"), true, __LINE__))
		return (false);
	return (true);
}

bool	invalid_test_get_error()
{
	if (!equal_or_err_b(aux.get_error_page(""), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page 404 /404.html"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page /404.html;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page 404 ;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page 404 /404;"), false, __LINE__))
		return (false);
	if (!equal_or_err_b(aux.get_error_page("error_page;"), false, __LINE__))
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
