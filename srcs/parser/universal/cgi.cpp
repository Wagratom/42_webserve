/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:26:29 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/15 11:32:44 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	extractExtension(std::string& line, std::string& extension)
{
	size_t	endExtension = line.find_first_of(" \t");

	if (endExtension == std::string::npos)
		return (write_error("Error: Invalid line cgi, no extension"));
	extension = line.substr(0, endExtension);
	line.erase(0, endExtension);
	while (line[0] == ' ' || line[0] == '\t')
		line.erase(0, 1);
	return (true);
}

static bool	extractPath(std::string& line, std::string& path)
{
	if (line.empty())
		return (write_error("Error: Invalid line cgi, no path"));
	path = line;
	return (true);
}

static bool	save_data(std::string extension, std::string path, aux_configuration* dst)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);
	Server_configuration*	server = dynamic_cast<Server_configuration*>(dst);

	if (server != NULL)
		server->set_cgi(extension, path);
	else if (location != NULL)
		location->set_cgi(extension, path);
	else
		return (write_error("Error in cast configuration in get_root"));
	return (true);
}

bool	Parser_configuration::get_cgi(std::string& line, aux_configuration* dst)
{
	std::string							extension;
	std::string							path;

	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line root, not ';'"));
	if (startsWithWord(line, "cgi") == false)
		return (false);
	if (extractPrefixWord(line, 3) == false)
		return (false);
	if (extractExtension(line, extension) == false)
		return (false);
	if (extractPath(line, path) == false)
		return (false);
	if (save_data(extension, path, dst) == false)
		return (false);
	std::cout << "extension: " << extension << std::endl;
	std::cout << "path: " << path << std::endl;
	return (true);
}
