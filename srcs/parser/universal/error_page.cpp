/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:25 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:29:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	is_digit_valid(std::string number)
{
	int	n_error;

	n_error = std::strtol(number.c_str(), NULL, 10);
	if (n_error < 400 || n_error > 599)
		return (write_error("Invalid error_page: invalid number error"));
	return (true);
}

static bool	valid_number_err(std::string aux)
{
	size_t	size_world;
	std::string	number;

	size_world = aux.find(" ");
	number = aux.substr(0, size_world);
	if (is_digit_valid(number) == false)
		return (false);
	if (aux.find(".") == std::string::npos)
		return (write_error("Invalid error_page: no extension in page"));
	return (true);
}

static bool	cut_error_page(std::string& aux)
{
	size_t	start;

	start = aux.find_first_not_of(" \t", 10);
	if (start == std::string::npos)
		return (write_error("Invalid error_page: no error_page"));
	aux = aux.substr(start);
	if (valid_number_err(aux) == false)
		return (false);
	return (true);
}

static bool	save_data(std::string& line, aux_configuration* dst)
{
	server_configuration* server = dynamic_cast<server_configuration*>(dst);
	location_configuration* location = dynamic_cast<location_configuration*>(dst);

	if (server != NULL)
		server->set_error_page(line);
	else if (location != NULL)
		location->set_error_page(line);
	else
		return (write_error("Error in cast configuration in error_page"));
	return (true);
}

bool	Parser_configuration::get_error_page(std::string& line, aux_configuration* dst)
{
	erase_comments(line);
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line error_page, not ';'"));
	if (valid_word(line, "error_page") == false)
		return (false);
	if (cut_error_page(line) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
