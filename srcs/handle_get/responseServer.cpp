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
	if (generetePathToResponse(tmp.path, _serverUsing->get_root(), _serverUsing->get_index()) == false)
		return (get_autoindex(_serverUsing->get_autoIndex(), _serverUsing->get_root()));
	if (getContentFile(tmp, _serverUsing->get_cgi(), "200 OK") == false)
	{
		if (tmp.notPermmision == true)
			return (responseClientError(ERROR403, _serverUsing->get_root(), getErrorPageMapServer("403")));
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500")));
	}
	if (sendResponseClient(tmp.content) == false)
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMapServer("500")));
	return (true);
}
