/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs_order_line.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:49:15 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/21 10:03:00 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Parser_request::save_requesition_line( void )
{
	size_t	pos;

	pos = _request.find("\n");
	if (pos == std::string::npos)
		return (write_error("save_requesition_line::Invalid request not order request line"));
	_order_request = _request.substr(0, pos);
	_request.erase(0, pos + 1);
	return (true);
}

bool	Parser_request::valid_requestion_line( std::string** verbs )
{
	if (_versionHTTP.compare("HTTP/1.1") != 0)
		return (write_error("set_server_protocol::Invalid  HTTP version: msg"));
	for (int i = 0; verbs[i]; i++)
	{
		if (_method == *verbs[i])
			return (true);
	}
	return (write_error("valid_requestion_line::Invalid orde request invalid method"));
}

bool	Parser_request::set_envs_order_line( std::string** verbs )
{
	if (!save_requesition_line())
		return (false);
	std::istringstream iss(_order_request);
	iss >> _method >> _endPoint >> _versionHTTP;
	if (!valid_requestion_line(verbs))
		return (false);
	setenv("SERVER_PROTOCOL", _versionHTTP.c_str(), 1);
	setenv("REQUEST_METHOD", _method.c_str(), 1);
	setenv("REQUEST_URI", _endPoint.c_str(), 1);
	write_debug_prefix("REQUEST_METHOD: ", _method);
	write_debug_prefix("REQUEST_URI: ", _endPoint);
	write_debug_prefix("SERVER_PROTOCOL: ", _versionHTTP);


	return (true);
}
