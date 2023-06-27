/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_return.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:35:59 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/27 14:23:52 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	removeReturnPrefix(std::string& LineErrorPage)
{
	size_t	initInfos = LineErrorPage.find_first_not_of(" \t", 6);

	if (initInfos == std::string::npos)
		return (write_error("Invalid error_page: no error_page"));
	LineErrorPage.erase(0, initInfos);
	return (true);
}

static bool	is_digit(std::string line)
{
	for (size_t i = 0; i < line.length(); i++)
	{
		if (isdigit(line[i]) == false)
			return (false);
	}
	return (true);
}

static bool	extractRedirect(std::string& LineReturn)
{
	size_t	endNumber = LineReturn.find_first_of(" \t");

	if (endNumber == std::string::npos)
		return (write_error("Invalid return: data is missing"));
	if (is_digit(LineReturn.substr(0, endNumber)) == false)
		return (write_error("Invalid return: data is not a number"));
	if (LineReturn.find_first_not_of(" \t", endNumber) == std::string::npos)
		return (write_error("Invalid return: no redirect"));
	return (true);
}

static bool	save_data(std::string& line, aux_configuration* dst)
{
	server_configuration* server = dynamic_cast<server_configuration*>(dst);
	location_configuration* location = dynamic_cast<location_configuration*>(dst);

	if (server != NULL)
		server->set_return(line);
	else if (location != NULL)
		location->set_return(line);
	else
		return (write_error("Error in cast configuration in get_root"));
	return (true);
}

bool	Parser_configuration::get_return(std::string& line, aux_configuration* dst)
{
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line root, not ';'"));
	if (startsWithWord(line, "return") == false)
		return (false);
	if (removeReturnPrefix(line) == false)
		return (false);
	if (extractRedirect(line) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
