/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 08:49:07 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:07:06 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	valid_index(std::string& line)
{
	size_t	pos = line.find_first_not_of(" \t", 5);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no index"));
	line = line.substr(pos);
	return (true);
}

bool	Parser_configuration::get_index(std::string& line)
{
	if (has_semicolon_at_end(line) == false)
		return (false);
	if (valid_word(line, "index") == false)
		return (false);
	if (valid_index(line) == false)
		return (false);
	server.index = line;
	return (true);
}
