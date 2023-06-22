/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 22:03:31 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	is_location(std::string line)
{
	if (line.find("location") == std::string::npos)
		return (false);
	if (line.find("{") == std::string::npos)
		return (false);
	return (true);
}

/*############################################################################*/
/*                            Init Parser                                     */
/*############################################################################*/

bool	Parser_configuration::controlParserConfiguration( void )
{
	write_debug("\033[0;36m\tStarting parser\033[0;34m");
	if (readConfigurationFile() == false)
		return (false);
	if (parserLineServer(_file[0]) == false)
		return (false);
	return (parserRestFile());
}

bool	Parser_configuration::parserRestFile( void )
{
	while (_file.size() != 0)
	{
		if (is_location(_file[0]))
		{
			if (parser_location() == false)
				return (false);
		}
		else
		{
			if (handle_server(_file[0]) == false)
				return (false);
		}
		_file.erase(_file.begin());
	}
	_file.clear();
	return (true);
}
