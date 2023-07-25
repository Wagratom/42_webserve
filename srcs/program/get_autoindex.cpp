/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_autoindex.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:49:32 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/24 09:22:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::get_autoindex( const bool& autoindex, const std::string& root)
{

	write_debug("get_autoindex");
	if (autoindex == false)
		return (responseClientError(ERROR404, _serverUsing->get_root(), getErrorPageMap(_errorMapUsing, "404")));
	try {
		auxReadFiles	tmp;

		bzero(&tmp, sizeof(tmp));
		tmp.path = AUTO_INDEX;
		setenv("CONTENT_LENGTH", "0", 1);
		setenv("PATHDIR", root.c_str(), 1);
		if (getContentFilePHP(tmp) == false)
		{
			if (tmp.notPermmision == true)
				return (responseClientError(ERROR403, _serverUsing->get_root(), getErrorPageMap(_errorMapUsing, "403")));
			return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_errorMapUsing, "500")));
		}
		if (sendResponseClient(tmp.content) == false)
			return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_errorMapUsing, "500")));
		return (true);
	} catch (std::exception& e) {
		write_error("get_autoindex: " + std::string(e.what()));
		return (responseClientError(ERROR500, _serverUsing->get_root(), getErrorPageMap(_errorMapUsing, "500")));
	}
}

