/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/17 20:29:13 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_GET_requesition( void )
{
	std::string endPoint = _parserRequest->get_endPoint();

	write_debug("handle_GET_requesition");
	try {
		_serverUsing = _serversConf.at(_port);
	} catch (std::exception& e) {
		return  write_error("handle_GET_requesition: " + std::string(e.what()));
	}
	responseClientGET(endPoint);
	return (handleKeepAlive());
}
