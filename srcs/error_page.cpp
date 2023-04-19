/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:25 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 09:40:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	is_digit_valid(std::string number)
{
	int	n_error;

	n_error = std::strtol(number.c_str(), NULL, 10);
	if (n_error < 400 || n_error > 599)
		return (write_error("Invalid error_page: invalid number"));
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

static void	save_error_page(std::string& aux, std::string& error_page)
{
	error_page = aux;
}

bool	Parser_configuration::get_error_page(char* line, std::string& error_page)
{
	std::string	aux;

	if (line == NULL)
		return (write_error("Invalid error_page: NULL"));
	if (get_aux_valid(aux, line) == false)
		return (false);
	if (valid_word(aux, "error_page") == false)
		return (false);
	if (cut_error_page(aux) == false)
		return (false);
	save_error_page(aux, error_page);
	return (true);
}
