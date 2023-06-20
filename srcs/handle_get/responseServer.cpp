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

bool	Server::responseServer(std::string status_code)
{
	auxReadFiles tmp;

	if (!generetePathToResponse(tmp.path, server()->get_root(), server()->get_index()))
		return (false);
	if (!getContentFile(tmp))
		return (false);
	generateDynamicHeader(tmp, status_code);
	tmp.response = tmp.header + tmp.content;
	return (sendResponseClient(tmp.response));
}
