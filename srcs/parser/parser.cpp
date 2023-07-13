/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:45 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 21:07:23 by wwallas-         ###   ########.fr       */
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
	write_debug_prefix(CIANO, "\tStarting parser");
	if (readConfigurationFile() == false)
		return (false);
	return (ParserConfigurationFile());
}

bool	Parser_configuration::ParserConfigurationFile( void )
{
	write_debug("ParserConfigurationFile...");
	while (_file.size() != 0)
	{
		// erase_comments(_file[0]);
		// if (_file[0].empty() || _file[0].find_first_not_of(" \t") == std::string::npos)
			// _file.erase(_file.begin());
		// else
		// {
		if (parserConfigurationServer() == false)
			return (false);
		_indexServer++;
		// }
	}
	return true;
}

bool	Parser_configuration::parserConfigurationServer( void )
{
	if (parserLineServer(_file[0]) == false)
		return (false);
	_server_configurations.push_back(new Server_configuration);
	while (_file.size() != 0)
	{
		// erase_comments(_file[0]);
		// if (_file[0].empty() || _file[0].find_first_not_of(" \t") == std::string::npos)
			// _file.erase(_file.begin());
		// else
		if (is_location(_file[0]))
		{
			if (parserLocation() == false)
				return (false);
		}
		else
		{
			if (_file[0][0] == '}')
				break;
			if (handle_server(_file[0]) == false)
				return (false);
		}
		_file.erase(_file.begin());
	}
	_file.erase(_file.begin());
	return (true);
}
