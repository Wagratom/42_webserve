/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseRequest.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:18:39 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/07 12:03:32 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::deleteParserRequest(bool status)
{
	delete _parserRequest;
	_parserRequest = NULL;
	return (status);
}

bool	Server::responseRequest( std::string& buffer )
{
	_parserRequest = new Parser_request(buffer);

	if (_parserRequest->set_envs_order_line(_verbs) == false)
		return (deleteParserRequest(false));
	if (_parserRequest->set_envs_header() == false)
		return (deleteParserRequest(false));
	if (_parserRequest->get_metodo() == "GET")
		return deleteParserRequest(handle_GET_requesition());
	if (_parserRequest->get_metodo() == "POST")
		return deleteParserRequest(handlePostRequest());
	if (_parserRequest->get_metodo() == "DELETE")
		return deleteParserRequest(handle_DELETE_requesition());
	return (deleteParserRequest(false));
}
