/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findLocation.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:24:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/16 09:34:19 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool Server::findLocation(const std::map<std::string, t_location*> locations, std::string& endPoint)
{
	size_t lastSlashPos;

	while (true)
	{
		if (locations.find(endPoint) != locations.end())
			return true;
		lastSlashPos = endPoint.find_last_of('/', endPoint.length() - 2);
		if (lastSlashPos == std::string::npos || lastSlashPos == 0)
			return false;
		endPoint.erase((lastSlashPos + 1));
	}
}
