/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_DELETE_requesition.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/07/12 20:14:12 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	Server::handle_DELETE_requesition( void )
{
	std::string	fileName = std::string(_parserRequest->get_endPoint(), 8);
	std::string	pathFile = "./uploads/" + fileName;

	write_debug("handle_DELETE_requesition");
	std::remove(pathFile.c_str());
	return (handleKeepAlive());
}
