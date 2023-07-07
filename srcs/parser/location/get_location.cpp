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

static bool	removeLocationPrefix(std::string& line)
{
	size_t	start = line.find_first_not_of(" \t", 8);

	if (start == std::string::npos)
		return (write_error("Error: removeLocationPrefix: Invalid line location: line empty"));
	if (line[start] != '/')
		return (write_error("Error: find_bar: Invalid line location: not found bar"));
	line.erase(0, start);
	return (true);
}

static bool	saveLocationName(std::string& line, std::string& locationName)
{
	size_t	endName = line.find_first_of(" \t");

	if (endName == std::string::npos)
		return (write_error("Error: saveLocationName: Invalid line location"));
	locationName = line.substr(0, endName);
	line.erase(0, endName);
	return (true);
}

static bool	checkOpeningBrace(std::string line)
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: checkOpeningBrace: Invalid line location: line empty"));
	if (line[start] != '{')
		return (write_error("Error: checkOpeningBrace: Invalid line location: not found key"));
	if (line.find_first_not_of(" \t", start + 1) != std::string::npos)
		return (write_error("Error: checkOpeningBrace: Invalid line location: after key"));
	return (true);
}

static bool	extractLocationName(std::string& line)
{
	std::string locationName;

	if (removeLocationPrefix(line) == false)
		return (false);
	if (saveLocationName(line, locationName) == false)
		return (false);
	if (checkOpeningBrace(line) == false)
		return (false);
	line = locationName;
	return (true);
}

static void	saveAndAppendSlash(std::string& dst, const std::string name)
{
	dst = name;
	if (dst[dst.length() - 1] != '/')
		dst.append("/");
}

bool	Parser_configuration::saveLocationName(std::string& locationName)
{
	std::string	locationLine = _file[0];

	if (removeIndentationAndComments(1, locationLine) == false)
		return (false);
	if (startsWithWord(locationLine, "location") == false)
		return (false);
	if (extractLocationName(locationLine) == false)
		return (false);
	saveAndAppendSlash(locationName, locationLine);
	_file.erase(_file.begin());
	return (true);
}
