/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:16:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:28:44 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	equal_or_err_i(int a, int b, int line)
{
	if (a != b)
	{
		std::cout << "\033[1;31mError: " << a << " != " << b << std::endl;
		std::cout << "\033[1;37m" << std::endl;
		std::cout << "Line: " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	different_or_err_i(int a, int b, int line)
{
	if (a == b)
	{
		std::cout << "\033[1;31mError: " << a << " == " << b << std::endl;
		std::cout << "\033[1;37m" << std::endl;
		std::cout << "Line: " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	equal_or_err_s(std::string a, std::string b, int line)
{
	if (a != b)
	{
		std::cout << "\033[1;31mError: " << a << " != " << b << std::endl;
		std::cout << "\033[1;37m" << std::endl;
		std::cout << "Line: " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	different_or_err_s(std::string a, std::string b, int line)
{
	if (a == b)
	{
		std::cout << "\033[1;31mError: " << a << " == " << b << std::endl;
		std::cout << "\033[1;37m" << std::endl;
		std::cout << "Line: " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	equal_or_err_b(bool a, bool b, int line)
{
	if (a != b)
	{
		std::cout << "\033[1;31mError: " << a << " != " << b << std::endl;
		std::cout << "\033[1;37m" << std::endl;
		std::cout << "Line: " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	different_or_err_b(bool a, bool b, int line)
{
	if (a == b)
	{
		std::cout << "\033[1;31mError: " << a << " == " << b << std::endl;
		std::cout << "\033[1;37m" << std::endl;
		std::cout << "Line: " << line << std::endl;
		return (false);
	}
	return (true);
}
