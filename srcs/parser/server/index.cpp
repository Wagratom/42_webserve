/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 08:49:07 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 13:56:29 by wwallas-         ###   ########.fr       */
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

static bool	save_data(std::string& line, Parser_configuration* dst)
{
	configuration_server* aux = dynamic_cast<configuration_server*>(dst);

	if (aux != NULL)
		aux->index = line;
	else {
		configuration_location* aux = dynamic_cast<configuration_location*>(dst);
		if (aux == NULL)
			return (write_error("Error casting server to configuration_location"));
		aux->index = line;
	}
	return (true);
}

bool	Parser_configuration::get_index(std::string& line, Parser_configuration *dst)
{
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line index, not ';'"));
	if (valid_word(line, "index") == false)
		return (false);
	if (valid_index(line) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
