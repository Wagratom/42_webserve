/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs_order_line.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:49:15 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/01 13:13:30 by wwallas-         ###   ########.fr       */
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
	return (true);
}

bool	Parser_request::set_method( void )
{
	size_t	pos;

	pos = _order_request.find("/");
	if (pos == std::string::npos)
		return (write_error_prefix("Invalid requesition line: get_verb"));

	_metodo = _order_request.substr(0, (pos - 1));
	_order_request.erase(0, pos);
	std::string aux = "REQUEST_METHOD=" + _metodo;
	_envs[_index_envs] = new char[aux.size() + 1];
	std::strcpy(_envs[_index_envs], aux.c_str());
	_index_envs++;
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

bool	Parser_request::set_request_url( void )
{
	size_t		pos;

	pos = _order_request.find(" ");
	if (pos == std::string::npos)
		return (write_error_prefix("Error: Parser_request: Invalid orde_request line")); // Defidir se falta de recurso é erro ou não
	_endPoint = _order_request.substr(0, pos);
	_order_request.erase(0, pos + 1);
	// std::string aux = "REQUEST_URI=" + _endPoint;
	// _envs[_index_envs++] = strdup(aux.c_str());
	return (true);
}

bool	Parser_request::set_server_protocol( void )
{
	if (_order_request.size() != 9)
		return (write_error_prefix("Invalid HTTP version: size"));
	if (_order_request != "HTTP/1.1\r")
		return (write_error_prefix("Invalid  HTTP version: msg"));
	std::string aux = "SERVER_PROTOCOL=" + _order_request.substr(0, 8);
	_envs[_index_envs] = new char[aux.size() + 1];
	std::strcpy(_envs[_index_envs], aux.c_str());
	_index_envs++;
	return (true);
}

bool	Parser_request::set_envs_order_line( std::string** verbs )
{
	if (!save_requesition_line())
		return (false);
	if (!set_method())
		return (false);
	if (!valid_verb(verbs))
		return (false);
	if (!set_request_url())
		return (false);
	if (!set_server_protocol())
		return (false);
	return (true);
}
