/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_requesition_line.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:30:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 21:47:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Parser::get_line(std::string& requesition_line)
{
	size_t		pos;

	pos = requesition.find("\n");
	if (pos == std::string::npos)
		return (write_msg_error("Invalid requesition line"));
	requesition_line = requesition.substr(0, pos);
	requesition.erase(0, pos + 1);
	write_debug_prefix("Requesition_line: ", requesition_line);
	return (true);
}

bool	Parser::valid_verb(std::string& verb)
{
	for (int i = 0; verbs[i]; i++)
	{
		if (verb == *verbs[i])
			return (true);
	}
	std::cout << "Invalid verb" << std::endl;
	return (write_msg_error("Invalid verb"));
}

bool	Parser::get_verb(std::string& requesition_line, std::string& verb)
{
	size_t		pos;

	pos = requesition_line.find("/");
	if (pos == std::string::npos)
		return (write_msg_error("Invalid requesition line"));

	verb = requesition_line.substr(0, (pos - 1));
	requesition_line.erase(0, pos + 1);
	write_debug_prefix("Verb: ", verb);
	return (true);
}

bool	Parser::parse_requesition_line( void )
{
	std::string	requesition_line;
	std::string	verb;

	if (!get_line(requesition_line))
		return (false);
	if (!get_verb(requesition_line, verb))
		return (false);
	if (!valid_verb(verb))
		return (false);
	return (true);

}
