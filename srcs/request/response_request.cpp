/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_request.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:18:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/01 13:53:22 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::deleteParserRequest(bool status)
{
	delete _parserRequest;
	_parserRequest = NULL;
	return (status);
}

bool	Server::response_request( std::string& buffer )
{
	bool	status = false;

	_parserRequest = new Parser_request(buffer);
	if (_parserRequest == NULL)
		return (write_error_prefix("Error: Server::parse_request: _parserFile is NULL"));
	if (_parserRequest->set_envs_order_line(_verbs) == false)
		return (deleteParserRequest(false));
	if (_parserRequest->set_envs_header() == false)
		return (deleteParserRequest(false));
	if (_parserRequest->get_metodo() == "GET")
		status = handle_GET_requesition();
	else if (_parserRequest->get_metodo() == "POST")
		status =  handle_POST_requesition();
	else if (_parserRequest->get_metodo() == "DELETE")
		status =  handle_DELETE_requesition();
	return (deleteParserRequest(status));
}
