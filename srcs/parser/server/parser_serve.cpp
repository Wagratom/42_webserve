/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_serve.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:31:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 09:57:47 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	Parser_configuration::handle_line_server(std::string& line)
{
	size_t	i = 0;

	line = line.substr(line.find_first_not_of(" \t"));
	while (dictionary[i].f)
	{
		if (line.compare(0, dictionary[i].key.size(), dictionary[i].key) == 0)
			return ((this->*dictionary[i].f)(line));
		i++;
	}

	std::cout << "Error: Invalid key: " << line << std::endl;
	return (false);
}

bool	Parser_configuration::handle_server( std::string line )
{
	int		end = 0;

	if (handle_line_server(this->file->line) == false)
	{
		if (line[0] == '}' && line[1] == '\0' && end++ == 0)
			return (true);
		return (false);
	}
	return (true);
}
