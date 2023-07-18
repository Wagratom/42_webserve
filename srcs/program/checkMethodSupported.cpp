/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkMethodSupported.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:19:38 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/17 21:45:13 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <web_server.hpp>

bool	Server::checkMethodSupported(std::vector<std::string> methods)
{
	std::string	method = getenv("REQUEST_METHOD");

	if (methods.empty())
		return (true);
	for (size_t i = 0; i < methods.size(); i++)
	{
		if (methods[i] == method)
			return (true);
	}
	write_error("Error: method not supported");
	return (false);
}

