/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_serve.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:31:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 13:51:34 by wwallas-         ###   ########.fr       */
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
	std::cout << "Error: Invalid line server: " << line << std::endl;
	return (false);
}

bool	Parser_configuration::handle_line_server(std::string& line)
{
	for (size_t i = 0; dictionary_server[i].f; i++) {
		if (line.compare(0, dictionary_server[i].key.size(), dictionary_server[i].key) == 0)
			return ((this->*dictionary_server[i].f)(line));
	}
	for (size_t i = 0; dictionary_universal[i].f; i++) {
		if (line.compare(0, dictionary_universal[i].key.size(), dictionary_universal[i].key) == 0)
			return ((this->*dictionary_universal[i].f)(line, this->server));
	}
	return (is_end_server(line));
}

bool	Parser_configuration::handle_server( std::string& line )
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: Invalid line server"));
	line = line.substr(start);
	return (handle_line_server(line));
}
