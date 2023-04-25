/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_location.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:38:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 15:56:35 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	is_end_server(std::string& line)
{
	if (line[0] == '}' && line[1] == '\0')
		return (true);
	std::cout << "Error: Invalid line location: " << line << std::endl;
	return (false);
}

static bool	avant_line(std::string& line)
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: Invalid line location"));
	line = line.substr(start);
	return (true);
}

bool	Parser_configuration::handle_location_line(std::string& line)
{
	size_t	i = 0;

	while (_dictionary_universal[i].f)
	{
		if (line.compare(0, _dictionary_universal[i].length, _dictionary_universal[i].key) == 0)
			return (this->*_dictionary_universal[i].f)(line, this->_location);
		i++;
	}
	return (false);
}

bool	Parser_configuration::parser_location( void )
{
	if (get_location(this->_file->line) == false)
		return (false);
	while (this->_file->next != NULL)
	{
		this->_file = this->_file->next;
		if (avant_line(this->_file->line) == false)
			return (false);
		if (handle_location_line(this->_file->line) == false)
			return (is_end_server(this->_file->line));
	}
	return (true);
}
