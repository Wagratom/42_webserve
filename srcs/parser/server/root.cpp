/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:26:29 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 13:55:15 by wwallas-         ###   ########.fr       */
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

static bool	save_data(std::string& line, Parser_configuration* dst)
{
	configuration_server* aux = dynamic_cast<configuration_server*>(dst);

	if (aux != NULL)
		aux->root = line;
	else {
		configuration_location* aux = dynamic_cast<configuration_location*>(dst);
		if (aux == NULL)
			return (write_error("Error casting server to configuration_location"));
		aux->root = line;
	}
	return (true);
}

bool	Parser_configuration::get_root(std::string& line, Parser_configuration* dst)
{
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line root, not ';'"));
	if (valid_word(line, "root") == false)
		return (false);
	if (valid_root(line) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
