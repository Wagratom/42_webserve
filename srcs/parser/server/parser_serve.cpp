/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_serve.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:31:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/22 16:16:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	is_end_server(std::string& line)
{
	static bool end = false;

	erase_comments(line);
	if (end == true)
		return (false);
	if (line[0] != '}' ||
		line.find_first_not_of(" \t", 1) != std::string::npos)
		return (write_error("Server: Incorrect closing brace '}'"));
	end = true;
	return (true);
}

bool	Parser_configuration::check_in_dict_server(std::string& line)
{
	size_t i = 0;

	while (_dictionary_server[i].f)
	{
		if (line.compare(0, _dictionary_server[i].key.size(), _dictionary_server[i].key) == 0)
			return ((this->*_dictionary_server[i].f)(line));
		i++;
	}
	return (false);
}

bool	Parser_configuration::check_in_dict_universal(std::string& line)
{
	for (std::map<std::string, directiveNginxUniversal>::iterator it = _dictionary_universal.begin(); it != _dictionary_universal.end(); ++it )
	{
		if (line.compare(0, it->first.size(), it->first) == 0)
			return (this->*(it->second))(line, _server_configuration);
	}
	return (false);
}

bool	Parser_configuration::handle_server( std::string& line )
{
	if (line[0] == '}')
		return (is_end_server(line));
	if (removeIndentationAndComments(1, line) == false)
		return (false);
	if (line.find_first_not_of(" \t") == std::string::npos)
		return (true);
	if (check_in_dict_server(line))
		return (true);
	return (check_in_dict_universal(line));
}
