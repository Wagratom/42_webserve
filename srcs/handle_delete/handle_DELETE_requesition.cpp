/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_DELETE_requesition.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:22:03 by wwallas-          #+#    #+#             */
/*   Updated: 2023/06/21 12:39:25 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>


static bool	delete_file_server(std::string fileName)
{
	std::string	pathFile = "./upload/" + fileName;

	if (std::remove(pathFile.c_str()) != 0)
		return (write_error("Error: handle_delete: Not possible to remove file"));
	return (true);
}

bool	Server::handle_DELETE_requesition( void )
{
	std::cout << "handle_DELETE_requesition" << std::endl;
	if (_parserRequest->get_endPoint().length() > 7)
		delete_file_server(std::string(_parserRequest->get_endPoint(), 8));
	return (responseClientDELETE());
}
