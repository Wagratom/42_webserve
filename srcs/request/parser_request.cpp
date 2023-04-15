/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/14 21:45:18 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

Parser::Parser(std::string const* const* verbs, std::string& requesition) : verbs(verbs) {
	this->requesition = std::string(requesition);
}

bool	Parser::write_msg_error(std::string message)
{
	std::cout << "Error: " << message << std::endl;
	return (false);
}

Parser::~Parser() {}

bool	Server::parse_request(std::string& buffer)
{
	Parser	parser(reinterpret_cast<std::string const* const*>(verbs), buffer);

	if (!parser.parse_requesition_line())
		return (false);
	return (true);
}

