/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:26:29 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:07:36 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	save_data(std::string& line, aux_configuration* dst)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);
	Server_configuration*	server = dynamic_cast<Server_configuration*>(dst);

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
	if (startsWithWord(line, "root") == false)
		return (false);
	if (extractPrefixWord(line, 4) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
