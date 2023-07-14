/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timeout.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:15:09 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser_configuration.hpp>

static bool	is_number_valid(std::string& port_string)
{
	int	i = 0;

	if (port_string.empty())
		return (write_error("Invalid port: empty port number"));
	if (port_string.length() > 5)
		return (write_error("Invalid port: port number too long"));
	while (port_string[i])
	{
		if (!isdigit(port_string[i]))
			return (write_error("Invalid port: port number is not a number"));
		i++;
	}
	return (true);
}

static bool	convertion_status(std::string& port_string)
{
	int	aux;

	aux = std::strtol(port_string.c_str(), NULL, 10);
	if (aux == 0 && port_string.length() != 1)
		return (write_error("Invalid port: port number is not a valid number"));
	if (aux == 0 && port_string[0] != '0')
		return (write_error("Invalid port: port number is not a valid number"));
	if (aux > 65535)
		return (write_error("Invalid port: port number is too big"));
	return (true);
}

static bool	convert_timeout(std::string& port_string)
{
	if (!is_number_valid(port_string))
		return (false);
	if (!convertion_status(port_string))
		return (false);
	return (true);
}

bool	Parser_configuration::get_timeout(std::string& timeout)
{
	Server_configuration*	tmp = dynamic_cast<Server_configuration*>(_server_configurations[_indexServer]);

	if (tmp == NULL)
		return (write_error("get_timeout:: In cast configuration"));
	if (has_semicolon_at_end(timeout) == false)
		return (write_error("get_timeout:: Invalid timeout line, not ';'"));
	if (startsWithWord(timeout, "timeout") == false)
		return (false);
	if (extractPrefixWord(timeout, 7) == false)
		return (false);
	if (convert_timeout(timeout) == false)
		return (false);
	tmp->set_port(std::strtol(timeout.c_str(), NULL, 10));
	return (true);
}
