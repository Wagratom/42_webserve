/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_max_body_size.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:06:27 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 17:28:53 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

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
	std::string aux(size);

	if (erase_validate_unit_measure(aux) == false)
		return (false);
	if (is_digit_status(aux) == false)
		return (false);
	return (true);
}

static bool	save_data(std::string& line, aux_configuration* dst)
{
	server_configuration* server = dynamic_cast<server_configuration*>(dst);
	location_configuration* location = dynamic_cast<location_configuration*>(dst);

	if (server != NULL)
		server->set_client_max_body_size(line);
	else if (location != NULL)
		location->set_client_max_body_size(line);
	else
		return (write_error("Error in cast configuration in client_max_body_size"));
	return (true);
}

bool	Parser_configuration::get_client_max_body_size(std::string& line, aux_configuration* dst)
{
	erase_comments(line);
	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line client_max_body_size, not ';'"));
	if (valid_word(line, "client_max_body_size") == false)
		return (false);
	erase_comments(line);
	if (get_max_body_size(line) == false)
		return (false);
	if (valid_max_body_size(line) == false)
		return (false);
	if (save_data(line, dst) == false)
		return (false);
	return (true);
}
