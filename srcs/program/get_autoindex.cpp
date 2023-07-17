/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_autoindex.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:49:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/17 20:00:45 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::get_autoindex( const bool& autoindex, const std::string& root)
{
	Server_configuration* server = _serversConf[_port];
	auxReadFiles	tmp;

	write_debug("get_autoindex");
	if (autoindex == false)
		return (responseClientError(ERROR404, server->get_root(), getErrorPageMapServer("404")));
	tmp.path = AUTO_INDEX;
	setenv("PATHDIR", root.c_str(), 1);
	if (getContentFilePHP(tmp) == false)
	{
		if (tmp.notPermmision == true)
			return (responseClientError(ERROR403, server->get_root(), getErrorPageMapServer("403")));
		return (responseClientError(ERROR500, server->get_root(), getErrorPageMapServer("500")));
	}
	if (sendResponseClient(tmp.content) == false)
		return (responseClientError(ERROR500, server->get_root(), getErrorPageMapServer("500")));
	return (true);
}

