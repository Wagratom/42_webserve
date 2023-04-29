/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:05:07 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	Parser_configuration::check_server( std::string& line )
{
	size_t	pos = line.find_first_not_of(" \t", 6);

	if (pos == std::string::npos)
		return (write_error("Error: Invalid line server"));
	if (line.compare(0, 6, "server") != 0)
		return (write_error("Error: Invalid line server"));
	if (line.compare(pos, 2, "{\0") != 0)
		return (write_error("Error: Invalid line server"));
	return (true);
}
