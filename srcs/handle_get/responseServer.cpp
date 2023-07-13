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
	write_debug("responseAutoIndexOrErrorServer");
	if (_serversConf[_port]->get_autoIndex() == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	if (responseClientListFiles(_serversConf[_port]->get_root().c_str(), "./root/autoindex.php") == false)
		return (responseClientError(ERROR500, getErrorPageMapServer("500")));
	return (true);

}

bool	Server::responseServer(std::string status_code)
{
	std::map<std::string, std::string*>	errorPages;
	auxReadFiles						tmp;

	write_debug("Response server");
	errorPages = _serversConf[_port]->get_error_page();
	if (!generetePathToResponse(tmp.path, _serversConf[_port]->get_root(), _serversConf[_port]->get_index()))
		return (responseAutoIndexOrErrorServer());
	if (!getContentFile(tmp))
		return (responseClientError(ERROR500, *(errorPages.find("500")->second)));
	generateDynamicHeader(tmp, status_code);
	tmp.response = tmp.header + tmp.content;
	if (sendResponseClient(tmp.response) == false)
		return (responseClientError(ERROR500, *(errorPages.find("500")->second)));
	tmp.response.clear();
	return (true);
}
