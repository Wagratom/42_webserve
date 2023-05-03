/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_order_line.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:25:37 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 13:27:54 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


bool	Parser_request::save_requesition_line( void )
{
	size_t	pos;

	pos = _request.find("\n");
	if (pos == std::string::npos)
		return (write_error_prefix("Error: Invalid request: not order request line"));
	_order_request = _request.substr(0, pos);
	_request.erase(0, pos + 1);
	write_debug_prefix("Requesition_line: ", _order_request);
	return (true);
}

bool	Parser_request::save_verb( void )
{
	size_t	pos;

	pos = _order_request.find("/");
	if (pos == std::string::npos)
		return (write_error_prefix("Invalid requesition line: get_verb"));

	_metodo = _order_request.substr(0, (pos - 1));
	_order_request.erase(0, pos);
	// write_debug_prefix("Verb: ", _metodo);
	return (true);
}

bool	Parser_request::valid_verb( std::string** verbs )
{
	for (int i = 0; verbs[i]; i++)
	{
		if (_metodo == *verbs[i])
			return (true);
	}
	return (write_error_prefix("Invalid verb: valid_verb"));
}

bool	Parser_request::save_endPoint( void )
{
	size_t		pos;

	pos = _order_request.find(" ");
	if (pos == std::string::npos)
		return (write_error_prefix("Error: Parser_request: Invalid orde_request line")); // Defidir se falta de recurso é erro ou não
	_endPoint = _order_request.substr(0, pos);
	_order_request.erase(0, pos + 1);
	// write_debug_prefix("endPoint: ", _endPoint);
	return (true);
}

bool	Parser_request::valid_htpp_version( void )
{
	if (_order_request.size() != 9)
		return (write_error_prefix("Invalid HTTP version: size"));
	if (_order_request != "HTTP/1.1\r")
		return (write_error_prefix("Invalid  HTTP version: msg"));
	return (true);
}

bool	Parser_request::parse_order_line( std::string** verbs )
{
	if (!save_requesition_line())
		return (false);
	if (!save_verb())
		return (false);
	if (!valid_verb(verbs))
		return (false);
	if (!save_endPoint())
		return (false);
	if (!valid_htpp_version())
		return (false);
	write_debug("\033[32mOrder Ok XD\n\033[0;37m");
	return (true);
}
