/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_name.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 14:42:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	get_server_names(std::string& line)
{
	size_t	start;

	start = line.find_first_not_of(" \t", 11);
	if (start == std::string::npos)
		return (write_error("Invalid server_name: no server name"));
	line = line.substr(start);
	return (true);
}

bool	Parser_configuration::get_server_name(std::string line)
{
	std::string	aux;

	if (get_aux_valid(aux, line) == false)
		return (false);
	if (valid_word(aux, "server_name") == false)
		return (false);
	if (get_server_names(aux) == false)
		return (false);
	server.server_name = aux;
	return (true);
}
