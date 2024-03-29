/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/14 12:12:33 by wwallas-         ###   ########.fr       */
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

static bool	convert_port(std::string& port_string)
{
	if (!is_number_valid(port_string))
		return (false);
	if (!convertion_status(port_string))
		return (false);
	return (true);
}

bool	Parser_configuration::get_port(std::string& listen)
{
	Server_configuration*	tmp = dynamic_cast<Server_configuration*>(_server_configurations[_indexServer]);

	if (tmp == NULL)
		return (write_error("get_port:: In cast configuration"));
	if (has_semicolon_at_end(listen) == false)
		return (write_error("get_port:: Invalid listen line, not ';'"));
	if (startsWithWord(listen, "listen") == false)
		return (false);
	if (extractPrefixWord(listen, 6) == false)
		return (false);
	if (convert_port(listen) == false)
		return (false);
	tmp->set_port(std::strtol(listen.c_str(), NULL, 10));
	return (true);
}
