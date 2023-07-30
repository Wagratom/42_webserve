/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendAutoindex.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:49:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/29 18:01:50 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendAutoindex( const bool& autoindex, const std::string& root)
{
	write_debug("sendAutoindex");
	if (autoindex == false)
		return (responseClientError(ERROR404, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "404")));
	_response->isProcessAutoindex = true;
	setenv("CONTENT_LENGTH", "0", 1);
	setenv("REQUEST_METHOD", "GET", 1);
	setenv("PATHDIR", root.c_str(), 1);
	setenv("GET", "autoindex", 1);
	try {
		auxReadFiles	tmp;

		bzero(&tmp, sizeof(tmp));
		tmp.path = AUTO_INDEX;
		if (getContentFilePHP(tmp) == false)
		{
			if (tmp.notPermmision == true)
				return (responseClientError(ERROR403, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "403")));
			return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "500")));
		}
		if (_response->hasProcess == true)
			return (true);
		if (sendResponseClient(tmp.content) == false)
			return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "500")));
		return (true);
	} catch (std::exception& e) {
		write_error("sendAutoindex: " + std::string(e.what()));
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_response->errorMap, "500")));
	}
}

