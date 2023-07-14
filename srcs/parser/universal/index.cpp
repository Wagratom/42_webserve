/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 08:49:07 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 13:48:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

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
		return (write_error("Invalid line index, not ';'"));
	if (startsWithWord(line, "index") == false)
		return (false);
	if (extractPrefixWord(line, 5) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
