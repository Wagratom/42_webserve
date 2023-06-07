/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_serve.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:31:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:28:49 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	is_end_server(std::string& line)
{
	static bool end = false;

	if (end == true)
		return (false);
	if (line[0] == '}' && line[1] == '\0')
	{
		end = true;
		return (true);
	}
	std::cout << "Error: Invalid line server: " << line << std::endl;
	return (false);
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
	size_t	i = 0;

	while (_dictionary_universal[i].f)
	{
		if (line.compare(0, _dictionary_universal[i].length, _dictionary_universal[i].key) == 0)
			return ((this->*_dictionary_universal[i].f)(line, this->_server_configuration));
		i++;
	}
	return (is_end_server(line));
}

bool	Parser_configuration::handle_server( std::string& line )
{
	size_t	start = line.find_first_not_of(" \t");

	erase_comments(line);
	if (start == std::string::npos)
		return (write_error("Error: Invalid line server"));
	line = line.substr(start);
	if (check_in_dict_server(line))
		return (true);
	return (check_in_dict_universal(line));
}
