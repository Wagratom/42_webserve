/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/13 12:23:26 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	writeStreerrorPrefix(std::string prefix)
{
	std::cerr << "\033[31m" <<  prefix << ": ";
	if (errno != 0)
		std::cerr << strerror(errno);
	std::cerr << AZUL << std::endl;
	return (false);
}

bool	write_error(std::string msg)
{
	std::cerr << "\033[31mError: " << msg;
	std::cerr << "\033[1;37m" << std::endl;
	return (false);
}

bool	write_error_prefixS(std::string prefix, std::string msg)
{
	std::cerr << "\033[31mError: " << prefix << msg << std::endl;
	std::cerr << "\033[1;37m" << std::endl;
	return (false);
}

bool	write_error_prefixI(std::string prefix, int number)
{
	std::cerr << "\033[31mError: " << prefix << number << std::endl;
	std::cerr << "\033[1;37m" << std::endl;
	return (false);
}
