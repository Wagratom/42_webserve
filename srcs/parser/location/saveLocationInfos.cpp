/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveLocationInfos.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:31:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/22 15:15:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	isNotEmptyLine(std::string line)
{
	return (line.find_first_not_of(" \t") != std::string::npos);
}

static bool	isEndServer(std::string& line)
{
	erase_comments(line);
	if (line[1] != '}' ||
		line.find_first_not_of(" \t", 2) != std::string::npos)
		return (write_error("Location: Incorrect closing brace '}'"));
	return (true);
}

bool	Parser_configuration::saveLocationInfos(t_location& location)
{
	std::string	lineLocation;

	while (_file.size() > 0)
	{
		lineLocation = _file[0];
		if (lineLocation[1] == '}')
			return (isEndServer(lineLocation));
		if (removeIndentationAndComments(2, lineLocation) == false)
			return (false);
		if (isNotEmptyLine(lineLocation) == false)
			return (true);
		if (handleLineLocation(lineLocation, location) == false)
			return (write_error("Location: Incorrect line: " + lineLocation));
		_file.erase(_file.begin());
	}
	return (true);
}

bool	Parser_configuration::handleLineLocation(std::string& line,  t_location& location)
{
	size_t	i = 0;

	while (_dictionary_universal[i].f)
	{
		if (line.compare(0, _dictionary_universal[i].length, _dictionary_universal[i].key) == 0)
			return (this->*_dictionary_universal[i].f)(line, location.configuration);
		i++;
	}
	return (false);
}

