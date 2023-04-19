/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:30:12 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/19 15:10:34 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.hpp>

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

bool	convertion_status(std::string& port_string)
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

static bool	get_valid_port(std::string& listen, std::string& aux_port)
{
	size_t	start = listen.find(" ");

	start = listen.find_first_not_of(" \t", 6);
	if (start == std::string::npos)
		return (write_error("Invalid line: no space after 'listen'"));
	aux_port = listen.substr(start);
	return (true);
}

bool	Parser_configuration::get_port(std::string listen)
{
	std::string	aux;
	std::string	aux_port;

	if (get_aux_valid(aux, listen) == false)
		return (false);
	if (valid_word(aux, std::string("listen")) == false)
		return (false);
	if (get_valid_port(aux, aux_port) == false)
		return (false);
	if (convert_port(aux_port) == false)
		return (false);
	server.port = std::strtol(aux_port.c_str(), NULL, 10);
	return (true);
}
