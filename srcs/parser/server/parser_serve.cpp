/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_serve.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:31:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:20:57 by wwallas-         ###   ########.fr       */
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

bool	Parser_configuration::handle_line_server(std::string& line)
{
	size_t	i = 0;

	while (dictionary[i].f)
	{
		if (line.compare(0, dictionary[i].key.size(), dictionary[i].key) == 0)
			return ((this->*dictionary[i].f)(line));
		i++;
	}
	return (is_end_server(line));
}

bool	Parser_configuration::handle_server( std::string line )
{
	size_t	start = line.find_first_not_of(" \t");

	if (start == std::string::npos)
		return (write_error("Error: Invalid line server"));
	line = line.substr(start);
	return (handle_line_server(line));
}
