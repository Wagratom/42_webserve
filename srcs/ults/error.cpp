/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 20:47:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	writeStreerrorPrefix(std::string prefix)
{
	std::cerr << "\033[31m" << std::endl;
	std::cerr << prefix << ": ";
	if (errno != 0)
		std::cerr << strerror(errno) << std::endl;
	std::cerr << "\033[0;37m" << std::endl;
	return (false);
}

bool	write_error(std::string msg)
{
	std::cerr << "\033[1;31mError: " << msg << std::endl;
	std::cerr << "\033[1;37m" << std::endl;
	return (false);
}

bool	write_error_prefixS(std::string prefix, std::string msg)
{
	std::cerr << "\033[1;31mError: " << prefix << msg << std::endl;
	std::cerr << "\033[1;37m" << std::endl;
	return (false);
}

bool	write_error_prefixI(std::string prefix, int number)
{
	std::cerr << "\033[1;31mError: " << prefix << number << std::endl;
	std::cerr << "\033[1;37m" << std::endl;
	return (false);
}

// bool	Parser_request::writeStreerrorPrefix(std::string prefix)
// {
// 	std::cout << "\033[31m" << std::endl;
// 	std::cout << prefix << ": ";
// 	if (errno != 0)
// 		std::cout << strerror(errno) << std::endl;
// 	std::cout << "\033[0;37m" << std::endl;
// 	return (false);
// }
