/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/29 10:33:14 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

Parser_request::Parser_request( std::string& request_client)
	: _request(request_client)
{};

Parser_request::~Parser_request() {}

bool	Parser_request::write_msg_error(std::string message)
{
	std::cout << "Error: " << message << std::endl;
	return (false);
}


bool	Server::parse_request(std::string& buffer)
{
	if (buffer.empty())
		return (true);
	if (_parser_request->parse_requesition_line(_verbs))
		return (true);
	write_debug_prefix("Requesition: ", "Success");
	return (true);
}

