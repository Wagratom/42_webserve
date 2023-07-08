/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getErrosPage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/08 10:05:57 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

std::string	Server::getErrorPageMapLocation(t_location* _location, std::string Error)
{
	std::map<std::string, std::string*>::iterator it;

	it = _location->configuration->get_error_page().find(Error);
	if (it == _location->configuration->get_error_page().end())
		return ("");
	return (*(it->second));
}

std::string	Server::getErrorPageMapServer(std::string Error)
{
	std::map<std::string, std::string*>::iterator it;

	it = server()[_indexServer2]->get_error_page().find(Error);
	if (it == server()[_indexServer2]->get_error_page().end())
		return ("");
	return (*(it->second));
}
