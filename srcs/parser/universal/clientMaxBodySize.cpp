/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientMaxBodySize.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:06:27 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:10:50 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	get_ValidateUnitMeasure(std::string& size, size_t& unidate)
{
	int		end = size.length() - 1;
	char	unit = size[end];

	if (unit != BYTES && unit != MEGABYTES && unit != KILOBYTES)
		return (write_error("Invalid client_max_body_size unit measure: must be K, M or G"));
	if (unit == BYTES)
		unidate = 1000;
	else if (unit == KILOBYTES)
		unidate = 1000000;
	else if (unit == MEGABYTES)
		unidate = 1000000000;
	size.erase(end);
	return (true);
}

static bool convertNumberToBits(std::string& size, size_t& unidate)
{
	int maxSize = std::atoi(size.c_str());

	if (maxSize <= 0)
		return write_error("Error: client_max_body_size: Value converted is less than 0");
	unidate *= maxSize;
	return true;
}

static bool	extractNumberConverted(std::string& size, size_t& unidate)
{
	if (get_ValidateUnitMeasure(size, unidate) == false)
		return (false);
	if (convertNumberToBits(size, unidate) == false)
		return (false);
	if (unidate > maximumSizeAllowed)
		return (write_error("Error: client_max_body_size: Value converted is bigger than 2GB"));
	return (true);
}

static bool	save_data(int maxSize, aux_configuration* dst)
{
	Location_configuration*	location = dynamic_cast<Location_configuration*>(dst);
	Server_configuration*	server = dynamic_cast<Server_configuration*>(dst);

	if (server != NULL)
		server->set_client_max_body_size(maxSize);
	else if (location != NULL)
		location->set_client_max_body_size(maxSize);
	else
		return (write_error("Error in cast configuration in client_max_body_size"));
	return (true);
}

bool	Parser_configuration::get_clientMaxBodySize(std::string& line, aux_configuration* dst)
{
	size_t	maxSize = 0;

	if (has_semicolon_at_end(line) == false)
		return (write_error("Error: Invalid line clientMaxBodySize, not ';'"));
	if (startsWithWord(line, "client_max_body_size") == false)
		return (false);
	if (extractPrefixWord(line, 20) == false)
		return (false);
	if (extractNumberConverted(line, maxSize) == false)
		return (false);
	if (save_data(maxSize, dst) == false)
		return (false);
	return (true);
}
