/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliares.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:28:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/20 11:43:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"
#pragma once

Parser_configuration aux;

bool	aux_server(std::string line, bool expected, int line_number)
{
	if (equal_or_err_b(aux.check_server(line), expected, line_number) == false)
		return (false);
	return (true);
}

bool	aux_serve_name(std::string line, bool expected, int line_number)
{
	if (equal_or_err_b(aux.get_server_name(line), expected, line_number) == false)
		return (false);
	return (true);
}

bool	aux_error_page(std::string line, bool expected, int line_number)
{
	if (equal_or_err_b(aux.get_error_page(line), expected, line_number) == false)
		return (false);
	return (true);
}


bool	aux_max_body_size(std::string line, bool expected, int line_number)
{
	if (equal_or_err_b(aux.get_client_max_body_size(line), expected, line_number) == false)
		return (false);
	return (true);
}

bool	aux_port(std::string line, bool expected, int line_number)
{
	if (equal_or_err_b(aux.get_port(line), expected, line_number) == false)
		return (false);
	return (true);
}

bool	aux_location(std::string line, bool expected, int line_number)
{
	if (equal_or_err_b(aux.get_location(line), expected, line_number) == false)
		return (false);
	return (true);
}

