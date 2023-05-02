/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/02 14:02:35 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Parser_request::write_msg_error(std::string message)
{
	std::cout << "Error: " << message << std::endl;
	return (false);
}

bool	Server::parse_request(std::string& buffer)
{
	_parser_request = new Parser_request(buffer);

	write_debug("Parsing request...");
	if (_parser_request == NULL)
		return (write_error_prefix("Error: Server::parse_request: _parser_file is NULL"));
	if (_parser_request->parse_requesition_line(_verbs) == false)
		return (false);
	// if (_parser_request->parse_headers() == false)
		// return (false);
	return (true);
}

