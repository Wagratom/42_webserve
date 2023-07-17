/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getErrosPage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:41:44 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/17 09:51:22 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

std::string	Server::getErrorPageMapLocation(t_location* _location, std::string Error)
{
	if (Error.empty())
		return ("");
	try {
		std::map<std::string, std::string*>	errorPages	= _location->configuration->get_error_page();
		std::string							pathError = *errorPages.at(Error);

		return (pathError);
	} catch (const std::out_of_range& e) {
		return ("");
	}
}

std::string	Server::getErrorPageMapServer(std::string Error)
{
	if (Error.empty())
		return ("");
	try {
		std::map<std::string, std::string*>	errorPages	= _serversConf.at(_port)->get_error_page();
		std::string							pathError = *errorPages.at(Error);

		return (pathError);
	} catch (const std::out_of_range& e) {
		return ("");
	}
}
