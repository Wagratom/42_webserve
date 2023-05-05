/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_request.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:18:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/05/05 15:57:27 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::parse_order_request( std::string& buffer )
{
	_parser_request = new Parser_request(buffer);

	if (_parser_request == NULL)
		return (write_error_prefix("Error: Server::parse_request: _parser_file is NULL"));
	if (_parser_request->set_envs_order_line(_verbs) == false)
		return (false);
	return (true);
}

bool	Server::response_request( std::string& buffer )
{
	if (parse_order_request(buffer) == false)
		return (false);
	if (_parser_request->get_metodo() == "GET")
		handle_GET_requesition();
	if (_parser_request->get_metodo() == "POST")
		std::cout << "Pediu POST" << std::endl;
	if (_parser_request->get_metodo() == "DELETE")
		std::cout << "Pediu DELETE" << std::endl;
	write_debug("\n");
	return (true);
}
