/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseClientGET.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/20 09:32:38 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::responseClientGET( std::string& endPoint)
{
	std::string	full_path = server()->get_root() + &endPoint[1];

	std::cout << "responseClientGET" << std::endl;
	if (endPoint == "/")
		return (responseServer("200"));
	if (endPoint == "/list/files/server")
		return (responseClientDELETE());
	if (isDirectory(full_path))
		return (responseLocation(endPoint));
	return (responseFile(endPoint));
}
