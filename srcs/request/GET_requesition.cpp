/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_requesition.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwallas- <wwallas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:35:31 by wwallas-          #+#    #+#             */
/*   Updated: 2023/04/30 17:45:36 by wwallas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <web_server.hpp>

bool	serv_webpage( std::ifstream& file)
{
	std::string		contentFile;
	std::string		buffer;

	return (true);
}
bool	Server::GET_requesition( void )
{
	std::ifstream	file;

	if (!open_file_index(file))
		std::cout << "Arquivo nao encontrado" << std::endl;
	if (serv_webpage(file) == false)
		return (false);
	return (true);
}

