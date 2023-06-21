/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 19:14:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

void	Parser_configuration::save_valid_line(std::string line)
{
	if (line.length() == 0)
		return ;
	if (line[0] == '#' || line[0] == '\n')
		return ;
	r_ft_lstadd_back(&(this->_file), r_ft_lstnew(line));
}

bool	Parser_configuration::readConfigurationFile( void )
{
	std::ifstream	file(_filename.c_str());
	std::string		line;

	write_debug("Opening/Reading file of confinguration...");
	if (file.is_open() == false)
		return (write_error("Error: File not found"));
	while (getline(file, line))
		save_valid_line(line);
	this->_save_init_file = this->_file;
	file.close();
	return (true);
}

bool	is_location(std::string& line)
{
	if (line.find("location") != std::string::npos)
		return (true);
	return (false);
}

/*############################################################################*/
/*                            Init Parser                                     */
/*############################################################################*/

bool	Parser_configuration::parseConfigurationFile( void )
{
	write_debug("\033[0;36m\tStarting parser\033[0;34m");
	if (readConfigurationFile() == false)
		return (false);
	if (check_server(this->_file->line) == false)
		return (false);
	if (parser_file() == false)
		return (false);
	write_debug("\033[32mOk XD\n\033[0;37m");
	return (true);
}

bool	Parser_configuration::parser_file()
{
	write_debug("Parsing file...");
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
