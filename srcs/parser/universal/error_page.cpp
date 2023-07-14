/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:25 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:09:37 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	extractErrorNumber(std::string& LineErrorPage, std::string& number)
{
	size_t	sizeNumber = LineErrorPage.find_first_of(" \t");
	int		n_error;

	if (sizeNumber == std::string::npos)
		return (write_error("Invalid error_page: no number error"));
	number = LineErrorPage.substr(0, sizeNumber);
	n_error = std::strtol(number.c_str(), NULL, 10);
	if (n_error < 400 || n_error > 599)
		return (write_error("Invalid error_page: invalid number error"));
	LineErrorPage.erase(0, sizeNumber);
	return (true);
}

static bool	extractPathErrorPage(std::string& LineErrorPage)
{
	size_t	initInfos = LineErrorPage.find_first_not_of(" \t");

	if (initInfos == std::string::npos)
		return (write_error("Invalid error_page: no error_page"));
	LineErrorPage.erase(0, initInfos);
	if (LineErrorPage.empty())
		return (write_error("Invalid error_page: no path error_page"));
	if (LineErrorPage.find(".") == std::string::npos)
		return (write_error("Invalid error_page: no extension in page"));
	return (true);
}

static bool	save_data(aux_configuration* dst, std::string number, std::string pathFileError)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);
	Server_configuration*	server = dynamic_cast<Server_configuration*>(dst);

	if (server != NULL)
		server->set_error_page(number, pathFileError);
	else if (location != NULL)
		location->set_error_page(number, pathFileError);
	else
		return (write_error("Error in cast configuration in error_page"));
	return (true);
}

bool	Parser_configuration::get_error_page(std::string& LineErrorPage, aux_configuration* dst)
{
	std::string	number;

	if (has_semicolon_at_end(LineErrorPage) == false)
		return (write_error("Error: Invalid LineErrorPage error_page, not ';'"));
	if (startsWithWord(LineErrorPage, "error_page") == false)
		return (false);
	if (extractPrefixWord(LineErrorPage, 10) == false)
		return (false);
	if (extractErrorNumber(LineErrorPage, number) == false)
		return (false);
	if (extractPathErrorPage(LineErrorPage) == false)
		return (false);
	if (save_data(dst, number, LineErrorPage) == false)
		return (false);
	return (true);
}
