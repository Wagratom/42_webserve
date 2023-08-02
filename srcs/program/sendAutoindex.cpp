/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendAutoindex.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:49:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/08/02 09:12:27 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::sendAutoindex( const bool& autoindex, const std::string& root)
{
	write_debug("sendAutoindex");
	if (autoindex == false)
		return (responseClientError("404", getErrorPageMap("404")));
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
				return (responseClientError("403", getErrorPageMap("403")));
			return (responseClientError("500", getErrorPageMap("500")));
		}
		if (_response->hasProcess == true)
			return (true);
		if (sendResponseClient(tmp.content) == false)
			return (responseClientError("500", getErrorPageMap("500")));
		return (true);
	} catch (std::exception& e) {
		write_error("sendAutoindex: " + std::string(e.what()));
		return (responseClientError("500", getErrorPageMap("500")));
	}
}

