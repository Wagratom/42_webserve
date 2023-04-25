/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_location.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:38:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 13:51:59 by wwallas-         ###   ########.fr       */
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


	while (dictionary_universal[i].f)
	{
		if (line.compare(0, dictionary_universal[i].key.length(), dictionary_universal[i].key) == 0)
			return (this->*dictionary_universal[i].f)(line, this->location);
		i++;
	}
	return (false);
}

bool	Parser_configuration::parser_location( std::string& line )
{
	std::cout << "parser_location" << std::endl;
	if (get_location(line) == false)
		return (false);
	while (this->file->next != NULL)
	{
		this->file = this->file->next;
		if (avant_line(this->file->line) == false)
			return (false);
		if (handle_location_line(this->file->line) == false)
			return (is_end_server(this->file->line));
	}
	return (true);
}
