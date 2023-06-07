/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_locationName.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:38:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:46 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	find_bar(std::string& line)
{
	size_t	start = line.find_first_not_of(" \t", 8);

	if (start == std::string::npos)
		return (write_error("Error: find_bar: Invalid line location: line empty"));
	if (line[start] != '/')
		return (write_error("Error: find_bar: Invalid line location: not found bar"));
	line = line.substr(start);
	return (true);
}

static bool	get_locationName(std::string& line, std::string& locationName)
{
	size_t	endName = line.find_first_of(" \t");

	if (endName == std::string::npos)
		return (write_error("Error: get_locationName: Invalid line location"));
	else
		locationName = line.substr(0, endName);
	line = line.substr(endName);
	return (true);
}

static bool	find_key(std::string line)
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: find_key: Invalid line location: line empty"));
	if (line[start] != '{')
		return (write_error("Error: find_key: Invalid line location: not found key"));
	if (line[start + 1] != '\0')
		return (write_error("Error: find_key: Invalid line location not terminate key"));
	return (true);
}

static bool	get_location_valid(std::string& line)
{
	std::string locationName;

	if (find_bar(line) == false)
		return (false);
	if (get_locationName(line, locationName) == false)
		return (false);
	if (find_key(line) == false)
		return (false);
	line = locationName;
	return (true);
}

bool	Parser_configuration::get_locationName(std::string& line, std::string& locationName)
{
	if (prepare_line(1, line) == false)
		return (false);
	if (valid_word(line, "location") == false)
		return (false);
	if (get_location_valid(line) == false)
		return (false);
	locationName = line;
	this->_file = this->_file->next;
	return (true);
}
