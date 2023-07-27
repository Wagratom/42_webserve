/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_serve.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:31:53 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/25 13:07:18 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

bool	Parser_configuration::checkDirectiveServer(std::string& line)
{
	for(std::map<std::string, directiveNginxServer>::iterator it = _dictionary_server.begin(); it != _dictionary_server.end(); ++it )
	{
		if (line.compare(0, it->first.size(), it->first) == 0)
			return (this->*(it->second))(line);
	}
	return (false);
}

bool	Parser_configuration::checkDirectiveUniversal(std::string& line)
{
	for (std::map<std::string, directiveNginxUniversal>::iterator it = _dictionary_universal.begin(); it != _dictionary_universal.end(); ++it )
	{
		if (line.compare(0, it->first.size(), it->first) == 0)
			return (this->*(it->second))(line, _server_configurations[_indexServer]);
	}
	return (write_error_prefixS("Error invalid Line: ", line));
}

bool	Parser_configuration::handle_server( std::string& line )
{
	if (removeIndentationAndComments(1, line) == false)
		return (false);
	if (checkDirectiveServer(line))
		return (true);
	return (checkDirectiveUniversal(line));
}
