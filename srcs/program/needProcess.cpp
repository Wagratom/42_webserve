/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:07:05 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/17 19:34:02 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

bool	Server::needProcess(const std::map<std::string, std::string>& cgi, const std::string& endPoint)
{
	write_debug("needProcess");
	std::string extension = endPoint.substr(endPoint.find_last_of(".") + 1);
	if (cgi.find(extension) != cgi.end())
		return (true);
	return (false);
}
