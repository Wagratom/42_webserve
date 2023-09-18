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

bool	deleteParserRequest(Parser_request*& parserRequest, bool status)
{
	delete parserRequest;
	parserRequest = NULL;
	return (status);
}

bool	Server::is_get_server(void)
{
	if (_parserRequest->get_endPoint() != "/")
		return true;
	if (_parserRequest->get_metodo() == "GET")
		return true;
	responseClientError("405", getErrorPageMap("405"));
	return (false);
}

bool	Server::seed_head_client( void ) {
	std::string content = "HTTP/1.1 405 OK\r\n";
	content += "Content-Type: text/html\r\n";
	content += "Content-Length: 0\r\n\r\n";
	sendResponseClient(content);
	return (true);
}

bool	Server::responseRequest( void )
{
	_parserRequest = new Parser_request(_response->buffer);

	write_debug_prefix(CIANO, "\t ENV Pasing");
	write_debug(AZUL);
	if (_parserRequest->set_envs_order_line(_verbs) == false)
		return (deleteParserRequest(_parserRequest, false));
	if (_parserRequest->set_envs_header() == false)
		return (deleteParserRequest(_parserRequest, false));
	if (_parserRequest->get_metodo() == "HEAD")
		return deleteParserRequest(_parserRequest, true), seed_head_client();
	if (is_get_server() == false)
		return (deleteParserRequest(_parserRequest, true));
	if (_parserRequest->get_metodo() == "GET")
		return deleteParserRequest(_parserRequest, handle_GET_requesition());
	if (_parserRequest->get_metodo() == "POST")
		return deleteParserRequest(_parserRequest, handlePostRequest());
	if (_parserRequest->get_metodo() == "DELETE")
		return deleteParserRequest(_parserRequest, handle_DELETE_requesition());
	return (deleteParserRequest(_parserRequest, false));
}
