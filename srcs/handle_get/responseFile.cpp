/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseFile.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 10:01:06 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool Server::responseFile(std::string endPoint)
{
	auxReadFiles tmp;

	std::cout << "responseFile" << std::endl;
	tmp.path = server()->get_root() + endPoint;
	if (!getContentFile(tmp))
		return (false);
	generateDynamicHeader(tmp, "200");
	send(_client_fd, tmp.header.c_str(), tmp.header.size(), 0);
	send(_client_fd, tmp.content.c_str(), tmp.content.size(), 0);
	return (true);
}
