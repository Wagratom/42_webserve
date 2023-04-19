/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 15:14:01 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	Parser_configuration::read_file(char* filename)
{
	std::ifstream	file(filename);
	std::string		line;

	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
	{
		if (line.empty())
			line = "\n";
		ft_lstadd_back(&(this->file), ft_lstnew(line));
	}
	file.close();
	return (true);
}

bool	handle_line(std::string line)
{
	(void)line;
	return (true);

}
bool	Parser_configuration::parser_server( void )
{
	if (get_server(this->file->line) == false)
		return (false);
	return (true);
}

bool	Parser_configuration::parser(char* filename)
{
	if (read_file(filename) == false)
		return (false);
	if (parser_server() == false)
		return (false);
	return (true);
}

