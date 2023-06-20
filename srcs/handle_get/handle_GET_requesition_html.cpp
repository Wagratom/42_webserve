/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_GET_requesition_html.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:35 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/19 21:15:23 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_GET_requesition_html( std::string& endPoint)
{
	std::string	full_path = server()->get_root() + endPoint;

	std::cout << "handle_GET_requesition_html" << std::endl;
	if (endPoint == "/")
		return (responseServer("200"));
	if (isDirectory(full_path))
		return (responseLocation(endPoint));
	return (responseFile(endPoint));
}
