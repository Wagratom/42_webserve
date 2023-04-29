/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:26:29 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	valid_root(std::string& line)
{
	size_t	pos = line.find_first_not_of(" \t", 4);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no root"));
	line = line.substr(pos);
	return (true);
}

static bool	save_data(std::string& line, aux_configuration* dst)
{
	server_configuration* server = dynamic_cast<server_configuration*>(dst);
	location_configuration* location = dynamic_cast<location_configuration*>(dst);

	if (server != NULL)
		server->set_root(line);
	else if (location != NULL)
		location->set_root(line);
	else
		return (write_error("Error in cast configuration in get_root"));
	return (true);
}

bool	Parser_configuration::get_root(std::string& line, aux_configuration* dst)
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
