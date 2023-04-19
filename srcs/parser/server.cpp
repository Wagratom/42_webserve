/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:43:36 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 14:10:19 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	Parser_configuration::get_server( std::string line )
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
