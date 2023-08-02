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
	std::map<std::string, std::string*>	errorPages = _response->errorPage;
	auxReadFiles						tmp;

	bzero(&tmp, sizeof(tmp));
	write_debug("Response server");
	_response->errorPage = _response->errorPage;
	if (generetePathToResponse(tmp.path, _response->root, _response->index) == false)
		return (sendAutoindex(_response->autoindex, _response->root));
	return (responseClient(tmp, _response->cgi, "200 OK"));
}
