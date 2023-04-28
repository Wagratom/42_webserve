/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_location.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:38:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/28 12:46:43 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	find_bar(std::string& line)
{
	size_t	start = line.find_first_not_of(" \t", 8);

	if (start == std::string::npos)
		return (write_error("Error: Invalid line location not found bar"));
	if (line[start] != '/')
		return (write_error("Error: Invalid line location not found bar"));
	line = line.substr(start);
	return (true);
}

static bool	find_key(std::string line)
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: Invalid line location"));
	if (line[start] != '{')
		return (write_error("Error: Invalid line location"));
	if (line[start + 1] != '\0')
		return (write_error("Error: Invalid line location not terminate key"));
	return (true);
}

static bool	get_location_valid(std::string& line)
{
	if (find_bar(line) == false)
		return (false);
	if (find_key(&line[1]) == false)
		return (false);
	return (true);
}

bool	Parser_configuration::get_location(std::string& line, std::string& location)
	{
		size_t	start = line.find_first_not_of(" \t");

		if (start == std::string::npos)
			return (write_error("Error: Invalid line location"));
		line = line.substr(start);
		if (valid_word(line, "location") == false)
			return (false);
		if (get_location_valid(line) == false)
			return (false);
		location = line;
		this->_file = this->_file->next;
		return (true);
	}
