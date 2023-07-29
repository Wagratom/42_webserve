/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:07:54 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/29 10:20:45 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool&	debug()
{
	static bool debug = false;
	return (debug);
}

int	get_debug()
{
	return (debug());
}

void	set_debug(bool	value)
{
	debug() = value;
	if (value == true)
		std::cout << "\t\033[0;31m\tDebug mode is on\033[0;37m" << std::endl;
	else
		std::cout << "\tDebug mode is off" << std::endl;
}

void	write_debug_number(std::string message, int number)
{
	if (!get_debug())
		return ;
	if (number != -1)
		std::cout << message << number << std::endl;
	else
		std::cout << message << std::endl;
}

bool	write_debug(std::string message)
{
	if (!get_debug())
		return true;
	std::cout << message << std::endl;
	return (false);
}

void	write_debug_prefix(std::string prefix, std::string message)
{
	if (!get_debug())
		return ;
	std::cout << prefix << message << std::endl;
}
