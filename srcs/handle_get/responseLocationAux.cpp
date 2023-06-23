/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseLocation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:15 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::createRootLocation(std::string& dst, const t_location* location)
{
	dst = location->configuration->get_root();
	if (dst.empty())
		dst = server()->get_root();
	if (dst.empty())
		return (write_error("Error: root not found"));
	return (true);
}

void	appendBar(std::string& str)
{
	if (str[str.length() - 1] != '/')
		str.append("/");
}
