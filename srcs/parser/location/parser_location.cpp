/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_location.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:38:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 13:02:02 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

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
	return (false);
}

static bool	avant_line(std::string& line)
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: Invalid line location"));
	line.substr(start);
	return (true);
}

bool	Parser_configuration::handle_line_location(std::string& line)
{
	size_t	i = 0;

	while (dictionary_location[i].f)
	{
		if (line.compare(0, dictionary_location[i].key.length(), dictionary_location[i].key) == 0)
			return (this->*dictionary_location[i].f)(line);
		i++;
	}
	return (is_end_server(line));
}

bool	Parser_configuration::handle_location_line(std::string& line)
{
	if (avant_line(line) == false)
		return (false);
	return (handle_line_location(line));
}

bool	Parser_configuration::parser_location( std::string& line )
{
	if (get_location(line) == false)
		return (false);
	while (this->file->next != NULL)
	{
		this->file = this->file->next;
		if (handle_location_line(this->file->line) == false)
			return (false);
	}
	return (true);
}
