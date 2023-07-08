/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_name.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 10:17:28 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	get_server_names(std::string& line)
{
	size_t	start;

	start = line.find_first_not_of(" \t", 11);
	if (start == std::string::npos)
		return (write_error("Invalid server_name: no server name"));
	line = line.substr(start);
	return (true);
}

bool	Parser_configuration::get_server_name(std::string& line)
{
	Server_configuration* aux = dynamic_cast<Server_configuration*>(_server_configurations[_indexServer]);

	if (aux == NULL)
		return (write_error("Error casting server to configuration_server"));
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line server_name, not ';'"));
	if (startsWithWord(line, "server_name") == false)
		return (false);
	if (get_server_names(line) == false)
		return (false);
	aux->set_server_name(line);
	return (true);
}
