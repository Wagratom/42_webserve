/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:16 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 09:19:34 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::write_error_prefix(std::string prefix)
{
	std::cout << "\033[31m" << std::endl;
	std::cout << prefix << ": ";
	if (errno != 0)
		std::cout << strerror(errno) << std::endl;
	std::cout << "\033[0;37m" << std::endl;
	return (false);
}

bool	Parser_request::write_error_prefix(std::string prefix)
{
	std::cout << "\033[31m" << std::endl;
	std::cout << prefix << ": ";
	if (errno != 0)
		std::cout << strerror(errno) << std::endl;
	std::cout << "\033[0;37m" << std::endl;
	return (false);
}
