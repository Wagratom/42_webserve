/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findLocationVector.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:53:46 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/18 11:45:40 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

bool	Server::findLocationVector(const std::map<std::string, t_location*>& locations, std::string& endPoint)
{
	size_t lastSlashPos;

	if (endPoint[endPoint.length() - 1] != '/')
		endPoint += "/";
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
