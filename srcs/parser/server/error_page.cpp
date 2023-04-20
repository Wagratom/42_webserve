/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:25 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 10:07:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

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

bool	Parser_configuration::get_error_page(std::string& line)
{
	if (has_semicolon_at_end(line) == false)
		return (false);
	if (valid_word(line, "error_page") == false)
		return (false);
	if (cut_error_page(line) == false)
		return (false);
	server.error_page = line;
	return (true);
}
