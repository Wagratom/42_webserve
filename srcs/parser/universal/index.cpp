/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 08:49:07 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 10:22:03 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	valid_index(std::string& line)
{
	size_t	pos = line.find_first_not_of(" \t", 5);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no index"));
	line = line.substr(pos);
	return (true);
}

static bool	save_data(std::string& line, aux_configuration* dst)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);
	Server_configuration*	server = dynamic_cast<Server_configuration*>(dst);

	if (server != NULL)
		server->set_index(line);
	else if (location != NULL)
		location->set_index(line);
	else
		return (write_error("Error in cast configuration in get_index"));
	return (true);
}

bool	Parser_configuration::get_index(std::string& line, aux_configuration *dst)
{
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line index, not ';'"));
	if (startsWithWord(line, "index") == false)
		return (false);
	if (valid_index(line) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
