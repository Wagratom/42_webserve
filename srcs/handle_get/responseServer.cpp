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

bool	Server::responseAutoIndexOrErrorServer( void )
{
	Server_configuration* server = _serversConf[_port];

	write_debug("responseAutoIndexOrErrorServer");
	if (server->get_autoIndex() == false)
		return (responseClientError(ERROR404, server->get_root(), getErrorPageMapServer("404")));
	if (responseClientListFiles(server->get_root().c_str(), AUTO_INDEX) == false)
		return (responseClientError(ERROR500, server->get_root(), getErrorPageMapServer("500")));
	return (true);

}

bool	Server::responseServer( void )
{
	Server_configuration*				server = _serversConf[_port];
	std::map<std::string, std::string*>	errorPages = server->get_error_page();
	auxReadFiles						tmp;

	write_debug("Response server");
	if (generetePathToResponse(tmp.path, server->get_root(), server->get_index()) == false)
		return (responseAutoIndexOrErrorServer());
	if (getContentFile(tmp, server->get_cgi()) == false)
	{
		if (tmp.notPermmision == true)
			return (responseClientError(ERROR403, server->get_root(), getErrorPageMapServer("403")));
		return (responseClientError(ERROR500, server->get_root(), getErrorPageMapServer("500")));
	}
	if (sendResponseClient(tmp.content) == false)
		return (responseClientError(ERROR500, server->get_root(), getErrorPageMapServer("500")));
	return (true);
}
