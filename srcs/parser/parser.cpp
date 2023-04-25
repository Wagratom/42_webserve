/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/25 17:13:02 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

void	Parser_configuration::save_valid_line(std::string line)
{

	if (line.length() == 0)
		return ;
	if (line[0] == '#' || line[0] == '\n')
		return ;
	ft_lstadd_back(&(this->_file), ft_lstnew(line));
}

bool	Parser_configuration::read_file(char* filename)
{
	std::ifstream	file(filename);
	std::string		line;

	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
		save_valid_line(line);
	file.close();
	return (true);
}

bool	is_location(std::string& line)
{
	if (line.find("location") != std::string::npos)
		return (true);
	return (false);
}

bool	Parser_configuration::parser_file()
{
	while (this->_file->next != NULL)
	{
		this->_file = this->_file->next;
		if (is_location(this->_file->line))
		{
			if (parser_location() == false)
				return (false);
		}
		else
		{
			if (handle_server(this->_file->line) == false)
				return (false);
		}
	}

	return (true);
}

bool	Parser_configuration::parser(char* filename)
{
	if (read_file(filename) == false)
		return (false);
	if (check_server(this->_file->line) == false)
		return (false);
	if (parser_file() == false)
		return (false);
	return (true);
}

