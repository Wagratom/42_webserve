/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_name.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/17 21:33:51 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	get_server_names(std::string& line, std::string& server_name)
{
	line.erase(0, 11);
	if (line.empty())
		return (write_error("Invalid server_name: no server name"));
	while (std::isspace(line[0]))
		line.erase(0, 1);
	if (line.empty())
		return (write_error("Invalid server_name: no server name"));
	server_name = line;
	return (true);
}

bool	get_server_name(char* line, std::string& server_name)
{
	std::string	aux;

	if (line == NULL)
		return (false);
	if (get_aux(aux, line) == false)
		return (false);
	if (valid_word(aux, "server_name") == false)
		return (false);
	if (get_server_names(aux, server_name) == false)
		return (false);
}
