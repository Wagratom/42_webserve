/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getErrosPage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/11 10:28:04 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

std::string	Server::getErrorPageMapLocation(t_location* _location, std::string Error)
{
	std::map<std::string, std::string*>::iterator	it;
	std::map<std::string, std::string*>				ErrorPages	= _location->configuration->get_error_page();

	it = ErrorPages.find(Error);
	if (it == ErrorPages.end())
		return ("");
	return (*(it->second));
}

std::string	Server::getErrorPageMapServer(std::string Error)
{
	std::map<std::string, std::string*>::iterator	it;
	std::map<std::string, std::string*>				ErrorPages	= server()[_port]->get_error_page();

	it = ErrorPages.find(Error);
	if (it == ErrorPages.end())
		return ("");
	return (*(it->second));
}
