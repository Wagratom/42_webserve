/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_requesition_line.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:30:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/16 16:54:56 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


bool	Parser::get_requesition_line(std::string& requesition_line)
{
	size_t		pos;

	pos = request.find("\n");
	if (pos == std::string::npos)
		return (write_error_prefix("Invalid requesition line: get_line"));
	requesition_line = request.substr(0, pos);
	request.erase(0, pos + 1);
	write_debug_prefix("Requesition_line: ", requesition_line);
	return (true);
}

bool	Parser::get_verb(std::string& requesition_line)
{
	size_t	pos;

	pos = requesition_line.find("/");
	if (pos == std::string::npos)
		return (write_error_prefix("Invalid requesition line: get_verb"));

	verb = requesition_line.substr(0, (pos - 1));
	requesition_line.erase(0, pos + 2);
	write_debug_prefix("Verb: ", verb);
	return (true);
}

bool	Parser::valid_verb(void)
{
	for (int i = 0; verbs[i]; i++)
	{
		if (verb == *verbs[i])
			return (true);
	}
	return (write_error_prefix("Invalid verb: valid_verb"));
}

bool	Parser::get_recurso(std::string& requesition_line)
{
	size_t		pos;

	pos = requesition_line.find(" ");
	if (pos == std::string::npos)
		return (true); // Defidir se falta de recurso é erro ou não
	recurso = requesition_line.substr(0, pos);
	requesition_line.erase(0, pos + 1);
	write_debug_prefix("Recurso: ", recurso);
	return (true);
}

bool	Parser::valid_htpp_version(std::string& requesition_line)
{
	std::cout << "requesition_line: " << requesition_line << std::endl;
	if (requesition_line.size() != 9)
		return (write_error_prefix("Invalid HTTP version: size"));
	if (requesition_line != "HTTP/1.1\r")
		return (write_error_prefix("Invalid  HTTP version: msg"));
	return (true);
}

bool	Parser::parse_requesition_line( void )
{
	std::string	requesition_line;

	if (!get_requesition_line(requesition_line))
		return (false);
	if (!get_verb(requesition_line))
		return (false);
	if (!valid_verb())
		return (false);
	if (!get_recurso(requesition_line))
		return (false);
	if (!valid_htpp_version(requesition_line))
		return (false);
	return (true);
}
