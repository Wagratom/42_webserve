/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:09:01 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 11:57:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../auxiliares.hpp"


bool	valid_test_get_error()
{
	if (!aux_error_page("error_page 404 /404.html;", true, __LINE__))
		return (false);
	if (!aux_error_page("error_page       404 /404.html;", true, __LINE__))
		return (false);
	if (!aux_error_page("error_page\t\t\t404 /404.html;", true, __LINE__))
		return (false);
	return (true);
}

bool	invalid_test_get_error()
{
	if (!aux_error_page("", false, __LINE__))
		return (false);
	if (!aux_error_page("error_page 404 /404.html", false, __LINE__))
		return (false);
	if (!aux_error_page("error_page /404.html;", false, __LINE__))
		return (false);
	if (!aux_error_page("error_page 404 ;", false, __LINE__))
		return (false);
	if (!aux_error_page("error_page 404 /404;", false, __LINE__))
		return (false);
	if (!aux_error_page("error_page;", false, __LINE__))
		return (false);
	return (true);
}

int main( void )
{
	if (!valid_test_get_error())
		return (1);
	if (!invalid_test_get_error())
		return (1);
	std::cout << "Suscess!" << std::endl;
	return (0);
}
