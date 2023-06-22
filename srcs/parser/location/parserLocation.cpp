/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserLocation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:31:50 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 22:50:42 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <Parser_configuration.hpp>

bool	alloc_location(t_location **location)
{
	*location = new t_location();

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
	if (line[0] != '}' ||
		line.find_first_not_of(" \t", 1) != std::string::npos)
		return (write_error("Location: Incorrect closing brace '}'"));
	return (true);
}

static bool	parser_location_err(t_location** location)
{
	delete (*location)->configuration;
	delete (*location);
	location = NULL;
	return (false);
}

/*############################################################################*/
/*                             INITIALIZE PARSER                              */
/*############################################################################*/

bool	Parser_configuration::parserLocation( void )
{
	t_location*	location = NULL;

	if (alloc_location(&location) == false)
		return (false);
	if (saveLocationName(location->endPoint) == false)
		return (parser_location_err(&location));
	if (configure_location(*location) == false)
		return (parser_location_err(&location));
	l_ft_lstadd_back(&(this->_location_configuration), location);
	return (true);
}

bool	Parser_configuration::configure_location(t_location& location)
{
	while (_file.size() > 0)
	{
		if (_file[0][1] == '}')
			return (is_end_server(_file[0]));
		if (configure_location_line(_file[0], location) == false)
			return (false);
		_file.erase(_file.begin());
	}
	return (true);
}

bool	Parser_configuration::configure_location_line(std::string line, t_location& location)
{

	if (removeIndentationAndComments(2, line) == false)
		return (false);
	if (line.find_first_not_of(" \t") == std::string::npos)
		return (true);
	if (handle_location_line(line, location) == false)
		return (write_error("Location: Incorrect line: " + line));
	return (true);
}

bool	Parser_configuration::handle_location_line(std::string& line,  t_location& location)
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
