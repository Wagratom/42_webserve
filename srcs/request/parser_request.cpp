/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/15 19:52:53 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

Parser::Parser(std::string const* const* verbs, std::string& requesition) : verbs(verbs) {
	this->request = std::string(requesition);
}
Parser::~Parser() {}

bool	Parser::write_msg_error(std::string message)
{
	std::cout << "Error: " << message << std::endl;
	return (false);
}


bool	Server::parse_request(std::string& buffer)
{
	if (buffer.empty())
		return (true);

	Parser	parser(reinterpret_cast<std::string const* const*>(verbs), buffer);
	if (!parser.parse_requesition_line())
		return (false);
	write_debug_prefix("Requesition: ", "Success");
	return (true);
}

