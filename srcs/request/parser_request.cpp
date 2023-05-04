/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:05:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/04 13:31:11 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::parse_request(std::string& buffer)
{
	_parser_request = new Parser_request(buffer);

	if (_parser_request == NULL)
		return (write_error_prefix("Error: Server::parse_request: _parser_file is NULL"));
	if (_parser_request->set_envs_order_line(_verbs) == false)
		return (false);
	if (_parser_request->set_envs_header() == false)
		return (false);
	return (true);
}
