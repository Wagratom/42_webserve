/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserLineServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:05:07 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/13 15:14:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	Parser_configuration::parserLineServer( std::string& line )
{
	size_t	pos = line.find_first_not_of(" \t", 6);

	erase_comments(line);
	if (pos == std::string::npos ||
		line.compare(0, 6, "server") != 0 ||
		line.compare(pos, 1, "{") != 0 ||
		line.find_first_not_of(" \t", pos + 1) != std::string::npos)
		return (write_error("Invalid line server"));
	_file.erase(_file.begin());
	return (true);
}
