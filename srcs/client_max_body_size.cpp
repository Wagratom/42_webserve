/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_max_body_size.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:06:27 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/18 13:26:05 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

static bool	get_max_body_size(std::string& aux)
{
	size_t	start;

	start = aux.find_first_not_of(" \t", 20);
	if (start == std::string::npos)
		return (write_error("Invalid client_max_body_size: no value"));
	aux = aux.substr(start);
	return (true);
}

static bool	erase_validate_unit_measure(std::string& size)
{
	int	end = size.length() - 1;

	if (size[end] != 'K' && size[end] != 'M' && size[end] != 'G')
		return (write_error("Invalid client_max_body_size unit measure: must be K, M or G"));
	size.erase(end);
	return (true);
}

static bool	is_digit_status(std::string& size)
{
	int	i = 0;

	while (size[i])
	{
		if (!isdigit(size[i]))
			return (write_error("Invalid client_max_body_size: value is not a number"));
		i++;
	}
	return (true);
}

static bool	valid_max_body_size(std::string& size)
{
	if (erase_validate_unit_measure(size) == false)
		return (false);
	if (is_digit_status(size) == false)
		return (false);
	return (true);
}

static void	save_max_body_size(std::string& size, std::string& client_max_body_size)
{
	client_max_body_size = size;
}

bool	get_client_max_body_size(char* line, std::string& client_max_body_size)
{
	std::string aux;

	if (get_aux_valid(aux, line) == false)
		return (false);
	if (valid_word(aux, "client_max_body_size") == false)
		return (false);
	if (get_max_body_size(aux) == false)
		return (false);
	if (valid_max_body_size(aux) == false)
		return (false);
	save_max_body_size(aux, client_max_body_size);
	return (true);
}
