/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseServer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 17:48:48 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::responseServer( void )
{
	std::map<std::string, std::string*>	errorPages = _serverUsing->get_error_page();
	auxReadFiles						tmp;

	bzero(&tmp, sizeof(tmp));
	write_debug("Response server");
	_response->errorMap = _serverUsing->get_error_page();
	if (generetePathToResponse(tmp.path, _serverUsing->get_root(), _serverUsing->get_index()) == false)
		return (sendAutoindex(_serverUsing->get_autoIndex(), _serverUsing->get_root()));
	return (responseClient(tmp, _serverUsing->get_cgi(), "200 OK"));
}
