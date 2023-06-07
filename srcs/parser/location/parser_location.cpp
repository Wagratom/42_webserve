/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_location.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:38:30 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:36 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	alloc_location(t_location_settings **location)
{
	*location = new t_location_settings();
	if (*location == NULL)
		return (write_error("Error: Memory allocation failed"));

	(*location)->configuration = new location_configuration();
	if ((*location)->configuration == NULL)
		return (write_error("Error: Memory allocation failed"));

	(*location)->next = NULL;
	return (true);
}

static bool	is_end_server(std::string& line)
{
	line.erase(0, 1);
	erase_comments(line);
	std::cout << "line: " << line << std::endl;
	if (line[0] != '}' ||
		line.find_first_not_of(" \t", 1) != std::string::npos)
		return (write_error("Location: Incorrect closing brace '}'"));
	return (true);
}

static bool	parser_location_err(t_location_settings** location)
{
	delete (*location)->configuration;
	delete (*location);
	location = NULL;
	return (false);
}

/*############################################################################*/
/*                             INITIALIZE PARSER                              */
/*############################################################################*/

bool	Parser_configuration::parser_location( void )
{
	t_location_settings*	location = NULL;

	if (alloc_location(&location) == false)
		return (false);
	if (get_locationName(this->_file->line, location->locationName) == false)
		return (parser_location_err(&location));
	if (configure_location(*location) == false)
		return (parser_location_err(&location));
	l_ft_lstadd_back(&(this->_location_configuration), location);
	return (true);
}

bool	Parser_configuration::configure_location(t_location_settings& location)
{
	while (this->_file != NULL)
	{
		if (this->_file->line[1] == '}')
			return (is_end_server(this->_file->line));
		if (prepare_line(2, this->_file->line) == false)
			return (false);
		if (handle_location_line(this->_file->line, location) == false)
			return (write_error("Location: Incorrect line: " + this->_file->line));
		this->_file = this->_file->next;
	}
	return (true);
}

bool	Parser_configuration::handle_location_line(std::string& line,  t_location_settings& location)
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
