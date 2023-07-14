/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliares.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:43:22 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:01:59 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	Parser_configuration::isLineEmpty(std::string& line)
{
	if (line.empty())
		return (true);
	if (line[0] == '#' || line[0] == '\n')
		return (true);
	erase_comments(line);
	if (line.find_first_not_of(" \t") == std::string::npos)
		return (true);
	return (false);
}

bool	has_semicolon_at_end(std::string& line)
{
	size_t	semicolon = line.find(';');

	if (semicolon == std::string::npos ||
		line.find_first_not_of(" \t", semicolon + 1) != std::string::npos ||
		isspace(line[semicolon -1]))
		return (false);
	line.erase(semicolon);
	return (true);
}

bool	startsWithWord(std::string& line, std::string word)
{
	size_t	lenghtWord = word.length();

	if (line.compare(0, lenghtWord, word) != 0)
		return (write_error("Invalid word: not " + word));
	if (line[lenghtWord] != ' ' && line[lenghtWord] != '\t')
		return (write_error("Invalid word: no space after " + word));
	return (true);
}

bool	extractPrefixWord(std::string& line, size_t lenghtErase)
{
	size_t	pos = line.find_first_not_of(" \t", lenghtErase);

	if (pos == std::string::npos)
		return (write_error("Invalid line: no word"));
	line = line.substr(pos);
	return (true);
}

/*                           PREPARE LINE                                     */
bool	removeIndentationAndComments(int indentation, std::string& line)
{
	if (line.empty() || !isspace(line[0]))
		return (write_error("Error: saveLocationName: Invalid line location"));
	erase_comments(line);
	if (line.find_first_not_of(" \t") == std::string::npos)
		return (true);
	if (line[0] == ' ')
		indentation *= 4;
	return (erase_isspaces(indentation, line));
}

void	erase_comments(std::string& line)
{
	size_t	pos = line.find('#');

	if (pos != std::string::npos)
		line.erase(pos);
}

bool	erase_isspaces(size_t indentation, std::string& line)
{
	size_t	i;
	char	c;

	i = 0;
	c = line[i];
	while (line[i] == c)
		i++;
	if (i != indentation)
		return (write_error("Error: erase_isspaces: Invalid indentation"));
	if (isspace(line[i]))
		return (write_error("Error: erase_isspaces: Invalid indentation"));
	line.erase(0, i);
	return (true);
}
