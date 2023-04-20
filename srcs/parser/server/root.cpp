/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:26:29 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:07:16 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	valid_root(std::string& line)
{
	size_t	pos = line.find_first_not_of(" \t", 4);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no root"));
	line = line.substr(pos);
	return (true);
}

bool	Parser_configuration::get_root(std::string& line)
{
	if (has_semicolon_at_end(line) == false)
		return (false);
	if (valid_word(line, "root") == false)
		return (false);
	if (valid_root(line) == false)
		return (false);
	server.root = line;
	return (true);
}
