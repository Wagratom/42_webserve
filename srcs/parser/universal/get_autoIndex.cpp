/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_autoIndex.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:19:36 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 10:21:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	extractAutoIndexPrefix(std::string& line)
{
	size_t	pos = line.find_first_not_of(" \t", 9);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no root"));
	line = line.substr(pos);
	return (true);
}

static bool	extractAutoIndex(std::string& autoIndexLine, bool& autoIndex)
{
	if (autoIndexLine == "on")
		autoIndex = true;
	else if (autoIndexLine == "off")
		autoIndex = false;
	else
		return (write_error("Invalid line: no root"));
	return (true);

}

static bool	save_data(bool autoIndex, aux_configuration* dst)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);
	Server_configuration*	server = dynamic_cast<Server_configuration*>(dst);

	if (server != NULL)
		server->set_autoIndex(autoIndex);
	else if (location != NULL)
		location->set_autoIndex(autoIndex);
	else
		return (write_error("Error in cast configuration in get_root"));
	return (true);
}

bool	Parser_configuration::get_autoIndex(std::string& line, aux_configuration* dst)
{
	bool	autoIndex;

	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line root, not ';'"));
	if (startsWithWord(line, "autoindex") == false)
		return (false);
	if (extractAutoIndexPrefix(line) == false)
		return (false);
	if (extractAutoIndex(line, autoIndex) == false)
		return (false);
	if (save_data(autoIndex, dst) == false)
		return (false);
	return (true);
}
