/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_page.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:19:25 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/18 13:29:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

bool	get_error_page(std::string& aux, std::string& error_page)
{
	size_t	start;

	start = aux.find_first_not_of(" \t", 10);
	if (start == std::string::npos)
		return (write_error("Invalid error_page: no error_page"));
	error_page = aux.substr(start);
	return (true);
}

void	save_error_page(std::string& aux, std::string& error_page)
{
	error_page = aux;
}

bool	get_error_page(char* line, std::string& error_page)
{
	std::string	aux;

	if (get_aux(line, aux) == false)
		return (false);
	if (valid_word(aux, "error_page") == false)
		return (false);
	if (get_error_page(aux, error_page) == false)
		return (false);
	save_error_page(aux, get_error_page);
	return (true);
}
